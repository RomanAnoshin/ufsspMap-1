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
    ui->pushSelPar->setMenu(createSelParMenu());
    ui->pushDisplayButton->setMenu(createDisplayMenu());
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
//    this->ui->displayX->display(point.x());
//    this->ui->displayY->display(point.y());
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
{   QMenu* menu=new QMenu(this);
    QMenu* first=new QMenu(trUtf8("Дислокация"), this);
    QMenu* second=new QMenu(trUtf8("Аэродромы"), this);
    QAction* third=new QAction(trUtf8("Сетка"), this);
    QAction* fourth=new QAction(trUtf8("Карта"), this);
    QAction* fifth=new QAction(trUtf8("Полосы"), this);
    QAction* sixth=new QAction(trUtf8("Трассы"), this);
    QAction* seventh=new QAction(trUtf8("Гран. ответ."), this);
    QAction* eight=new QAction(trUtf8("зоны и рубежи"), this);
    menu->addMenu(first);
    menu->addMenu(second);
    second->addAction("Все аэродромы",upointer,SLOT(airfieldAll()));
    second->addAction("Свои",upointer,SLOT(airfieldOwn()));
    second->addAction("Чужие",upointer,SLOT(airfieldForeign()));
    menu->addAction(third);
    menu->addAction(fourth);
    menu->addAction(fifth);
    menu->addAction(sixth);
    menu->addAction(seventh);
    menu->addAction(eight);
    return menu;
}
QMenu * MainMap::createSelParMenu()
{   QMenu* menu=new QMenu(this);
    QMenu* first=new QMenu(trUtf8("По ОГП"), this);
    QMenu* second=new QMenu(trUtf8("По ИВО"), this);
    QAction* third=new QAction(trUtf8("По скорости"), this);
    QAction* fourth=new QAction(trUtf8("По высоте"), this);
    QAction* fifth=new QAction(trUtf8("Тренажные"), this);
    QAction* sixth=new QAction(trUtf8("Рефльные"), this);
    QAction* seventh=new QAction(trUtf8("Головные"), this);
    QAction* eight=new QAction(trUtf8("Без этала"), this);
    QAction* ninth=new QAction(trUtf8("Опасн. близ"), this);
    menu->addMenu(first);
    menu->addMenu(second);
    first->addAction("Свои");
    first->addAction("Чужой",upointer,SLOT(showAirForeign()));
    first->addAction("Не опознанный");
    menu->addAction(third);
    menu->addAction(fourth);
    menu->addAction(fifth);
    menu->addAction(sixth);
    menu->addAction(seventh);
    menu->addAction(eight);
    menu->addAction(ninth);
    return menu;
}

QMenu *MainMap::createDisplayMenu()
{
     QMenu* menu=new QMenu(this);
     QMenu* first=new QMenu(trUtf8("Предыстория"), this);
     QMenu* second=new QMenu(trUtf8("Вызов Лупы"), this);
     QMenu* third=new QMenu(trUtf8("Форм. по ВО"), this);
     QAction* fourth=new QAction(trUtf8("Справки ХАР"), this);
     QAction* fifth=new QAction(trUtf8("Обмен"), this);
     QAction* sixth=new QAction(trUtf8("Пеленги"), this);
     QAction* seventh=new QAction(trUtf8("Спец.Форм"), this);
     QAction* eight=new QAction(trUtf8("Коорд. мар."), this);
     menu->addMenu(first);
     menu->addMenu(second);
     menu->addMenu(third);
     third->addAction("Местополож ВО");
     third->addAction("NE(NBO)");
     third->addAction("ИВО,ТВО,NE(NBO)");
     third->addAction("ИВО,ТВО,NE(NBO),H,V",upointer,SLOT(drawRefefenceForm()));
     third->addAction("Отобразить NBO");
     menu->addAction(fourth);
     menu->addAction(fifth);
     menu->addAction(sixth);
     menu->addAction(seventh);
     menu->addAction(eight);
     return menu;
}

void MainMap::on_pushButton_34_clicked()
{
    upointer->drawRefefenceForm();
}
