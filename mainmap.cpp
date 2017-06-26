#include "mainmap.h"
#include "ui_mainmap.h"
#include <QCoreApplication>
#include <QDesktopWidget>
#include <QDir>

MainMap::MainMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMap)
{
    ui->setupUi(this);

    QString confDir = QCoreApplication::applicationDirPath()+"/conf/";
    QDir dir(confDir);
    if(!dir.exists() && !dir.mkdir(confDir)){
        //error
    }
    upointer = new UPointer(confDir);
    ui->graphicsView->setScene(upointer->getScene());
    upointer->reWrite(ui->graphicsView->width(),ui->graphicsView->height());
    admin = new AdminForm();
    admin->setPointer(upointer);
    // отображение положения курсора на сцене в Дисплее
    connect(upointer->getScene(), SIGNAL(signalCursor(QPointF)), this,SLOT(slotDisplay(QPointF)));
    ui->graphicsView->setMouseTracking(true);
    this->ui->label_2->setStyleSheet("background-color: rgb(56, 235,229)");
    this->setSubButtonStYle();
    QTimer* timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setDateTime()));
    timer->start(1000);

    ui->pushButtonStatic->setMenu(createStaticMenu());

}
void MainMap::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);
    upointer->reWrite(ui->graphicsView->width(),ui->graphicsView->height());
}

void MainMap::mousePressEvent(QMouseEvent *mouse){
    QPoint pf = mouse->pos();
    upointer->setPoint(pf);
}

void MainMap::slotDisplay(QPointF point)
{
    this->ui->displayX->display(point.x());
    this->ui->displayY->display(point.y());
}

MainMap::~MainMap()
{
    delete ui;
}

void MainMap::on_btnRG_clicked()
{
    admin->setGeometry(QStyle::alignedRect(
                           Qt::LeftToRight,
                           Qt::AlignCenter,
                           admin->size(),
                           qApp->desktop()->availableGeometry()
                           ));
    admin->show();
}

void MainMap::setDateTime()
{
    QDateTime DaTi=QDateTime::currentDateTime();
    ui->label->setText(DaTi.date().toString("dd-MM")+
   "  "+DaTi.time().toString("hh:mm:ss"));
}

void MainMap::setSubButtonStYle()
{
    ui->subButton->setStyleSheet("color: rgb(195, 175,8)");
    ui->subButton->setEnabled(false);
    ui->subButton2->setStyleSheet("color: rgb(195, 175,8)");
    ui->subButton2->setEnabled(false);
    ui->subButton3->setStyleSheet("color: rgb(195, 175,8)");
    ui->subButton3->setEnabled(false);

}

QMenu * MainMap::createStaticMenu()
{   QMenu * menu=new QMenu(this);
    QAction* first=new QAction(trUtf8("Показать свои"), this);
    QAction* second=new QAction(trUtf8("Показать чужии"), this);
    menu->addAction(first);
    menu->addAction(second);
    return menu;
}



