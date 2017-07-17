#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QFile>
#include <QIODevice>
#include "adminform.h"
#include "ui_adminform.h"

AdminForm::AdminForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    lockPoint = false;
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(onDrawAirPoint(int)));
    connect(ui->numberPath, SIGNAL(activated(QString)),this, SLOT(parseValueToInt(QString)));
    connect(ui->OGP,SIGNAL(activated(int)),this,SLOT(setOGP(int)));
    connect(ui->typeAirObject,SIGNAL(activated(int)),this, SLOT(setTypeAirObject(int)));
    connect(ui->IndexAirObj,SIGNAL(activated(int)),this,SLOT(setIndex(int)));
    connect(ui->speedEdit,SIGNAL(textEdited(QString)),this,SLOT(setSpeed(QString)));
    connect(ui->heightEdit,SIGNAL(textEdited(QString)),this,SLOT(setHeightFly(QString)));
    connect(ui->quantityEdit,SIGNAL(textEdited(QString)),this,SLOT(setQuantity(QString)));
    connect(ui->numberPathPoint, SIGNAL(activated(int)),this, SLOT(onNumberPathPointSelect(int)));
}

AdminForm::~AdminForm()
{
    delete ui;
}

void AdminForm::on_bgImg_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Файл карты"), upointer->getConfDir(),
                                                    tr("Изображения (*.png);;Все файлы (*.*)"));
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        file.close();
        QString oldImgPath = upointer->getConfDir()+"mainMap.png";
        ui->bgLine->setText(fileName);
        QFile fileOld(oldImgPath);
        if(fileOld.exists())
            fileOld.remove();
        QFile::copy(fileName,oldImgPath);
        upointer->setBg(oldImgPath);

    }
}
void AdminForm::setPointer(UPointer *up){
    upointer = up;
    lockPoint = true;
    ui->bgLine->setText(upointer->getBg());
    fPoint zPoint = upointer->getzPosition();
    ui->x0->setValue((double)zPoint.x);
    ui->y0->setValue((double)zPoint.y);
    fPoint lastPoint = upointer->getlastPosition();
    ui->x1->setValue((double)lastPoint.x);
    ui->y1->setValue((double)lastPoint.y);
    lockPoint = false;
    for(auto &el:upointer->getConfig().airObject)
        ui->numberPath->addItem(QString::number(el.targetNumber),1);
    countTargetNumber=upointer->getConfig().airObject.size();
    installOGP();
    installTypeAirObject();
    installIndex();
    ui->numberPath->setCurrentIndex(0);
    loadTabTraining();
}

void AdminForm::reloadNumberPathPoint()
{
    ui->numberPathPoint->clear();
    path=upointer->getScene()->getPath();
    instalSettingsPath();
}

void AdminForm::onNumberPathPointSelect(int i)
{
    upointer->getScene()->selectInNumberPathPoint=i;
    upointer->getScene()->drawPath();
}

void AdminForm::setOGP(int i)
{
    upointer->getScene()->setOGP(i);
}

void AdminForm::setTypeAirObject(int i)
{
    upointer->getScene()->setTypeAirObject(i);
}

void AdminForm::setSpeed(QString speed)
{

    upointer->getScene()->setSpeed(speed.toInt());
}

void AdminForm::setHeightFly(QString heightFly)
{
    upointer->getScene()->setHeightFly(heightFly.toInt());
}

void AdminForm::setIndex(int index)
{
    upointer->getScene()->setIndex(index);
}

void AdminForm::setQuantity(QString quantity)
{
    upointer->getScene()->setQuantity(quantity.toInt());
}

void AdminForm::on_addLine_clicked()
{
    iDataLines dl;
    dl.bold = ui->bold->value();
    dl.color = QColor(ui->red->value(),ui->green->value(),ui->blue->value());
    QList <fPoint> data;
    dl.data = data;
    upointer->createLine(&dl);
}

void AdminForm::on_x0_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint)
        upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_y0_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint) upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_x1_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint) upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_y1_valueChanged(double arg1)
{
    Q_UNUSED(arg1)
    if(!lockPoint) upointer->setPosition((float)ui->x0->value(),(float)ui->y0->value(),(float)ui->x1->value(),(float)ui->y1->value());
}

void AdminForm::on_newPath_clicked()

{   upointer->getScene()->deleteSceneItem();
    flightRoute newPath;
    newPath.targetNumber=++countTargetNumber;
    newPath.OGP=2;
    newPath.typeAirObj=0;
    newPath.index=0;
    upointer->getScene()->setIsCreatePath(true);
    upointer->getScene()->setPath(newPath);
    upointer->addConfAir(newPath);
    ui->numberPath->addItem(QString::number(newPath.targetNumber),1);
    path=newPath;
    ui->numberPath->setCurrentIndex(newPath.targetNumber-1);
    ui->typeAirObject->setCurrentIndex(path.typeAirObj);
    ui->OGP->setCurrentIndex(path.OGP);
    ui->IndexAirObj->setCurrentIndex(path.index);
    ui->speedEdit->setText(QString::number(path.speed));
    ui->heightEdit->setText(QString::number(path.heightFly));
    ui->quantityEdit->setText(QString::number(path.quantity));
    ui->numberPathPoint->clear();
}

void AdminForm::on_deletePath_clicked()
{
    int i=ui->numberPathPoint->currentIndex();
    path.airPoint.removeAt(i);
    upointer->getScene()->deleteSceneItem();
    upointer->getScene()->setPath(path);
    upointer->getScene()->drawPath();
    ui->numberPathPoint->clear();
    int count=1;
    for(auto &el:path.airPoint){
        ui->numberPathPoint->addItem(QString::number(count++),1);
    }
}

void AdminForm::on_saveNewPath_clicked()
{
    path=upointer->getScene()->getPath();
    if(!path.airPoint.isEmpty())
        upointer->reWritePath(path);
    upointer->save();
}

void AdminForm::installOGP()
{
    ui->OGP->addItem("Свой",1);
    ui->OGP->addItem("Чужой",2);
    ui->OGP->addItem("Неопознан",3);
}
void AdminForm::installTypeAirObject()
{
    ui->typeAirObject->addItem("Самолет",1);
    ui->typeAirObject->addItem("Ракета",2);
    ui->typeAirObject->addItem("Вертолет",3);
    ui->typeAirObject->addItem("Космический аппарат",4);
}

void AdminForm::installIndex()
{
    ui->IndexAirObj->addItem("ИВО не определен",1);
    ui->IndexAirObj->addItem("Воздушный противник",2);
    ui->IndexAirObj->addItem("Пост. актив. помех",3);
    ui->IndexAirObj->addItem("Заявочный самолет",4);
    ui->IndexAirObj->addItem("Самолет НРП",5);
    ui->IndexAirObj->addItem("Контрольный самолет",6);
    ui->IndexAirObj->addItem("Сам. выполняющий БЗ",7);
    ui->IndexAirObj->addItem("Индекс не установлен",8);
}

void AdminForm::isActiveComboBox(bool isActive)
{
    if(!isActive){
        ui->OGP->setItemData(0," ", Qt::UserRole - 1);
        ui->OGP->setItemData(1," ", Qt::UserRole - 1);
        ui->OGP->setItemData(2," ", Qt::UserRole - 1);

        ui->typeAirObject->setItemData(0," ", Qt::UserRole - 1);
        ui->typeAirObject->setItemData(1," ", Qt::UserRole - 1);
        ui->typeAirObject->setItemData(2," ", Qt::UserRole - 1);
    }
    else{
        ui->OGP->setItemData(0," ", Qt::UserRole);
        ui->OGP->setItemData(1," ", Qt::UserRole);
        ui->OGP->setItemData(2," ", Qt::UserRole);

        ui->typeAirObject->setItemData(0," ", Qt::UserRole );
        ui->typeAirObject->setItemData(1," ", Qt::UserRole );
        ui->typeAirObject->setItemData(2," ", Qt::UserRole );
    }

}


void AdminForm::onDrawAirPoint(int i)
{       upointer->getScene()->deleteSceneItem();
        if(i!=2){
            upointer->getScene()->setIsCreatePath(false);
            upointer->getScene()->deleteSceneItem();
        }
        if(i==3){
            loadTabTraining();
            upointer->getScene()->drawPathAll();
        }
}

void AdminForm::parseValueToInt(QString s)
{
    upointer->getScene()->setIsCreatePath(true);
    isActiveComboBox(true);
    int i=s.toInt();
    upointer->getScene()->deleteSceneItem();
    path=upointer->getConfig().airObject.at(i-1);
    instalSettingsPath();
    connect(upointer->getScene(), SIGNAL(signalCreateNewPathPoint()),this,SLOT( reloadNumberPathPoint()));
}
void AdminForm::instalSettingsPath()
{
    upointer->getScene()->setPath(path);
    upointer->getScene()->drawPath();
    int count=1;
    ui->numberPathPoint->clear();
    for(auto &el:path.airPoint){
        ui->numberPathPoint->addItem(QString::number(count++),1);
    }
    ui->OGP->setCurrentIndex(path.OGP);
    ui->typeAirObject->setCurrentIndex(path.typeAirObj);
    ui->IndexAirObj->setCurrentIndex(path.index);
    ui->speedEdit->setText(QString::number(path.speed));
    ui->heightEdit->setText(QString::number(path.heightFly));
    ui->quantityEdit->setText(QString::number(path.quantity));
}

void AdminForm::loadTabTraining()
{
    ui->listWidgetFirst->clear();
    for(auto &el:upointer->getConfig().airObject)
        ui->listWidgetFirst->addItem(QString::number(el.targetNumber));
}



void AdminForm::on_addItem_clicked()
{   bool b=true;
    QModelIndex i=ui->listWidgetFirst->currentIndex();
    if(i.row()>=0){
        flightRoute myPath=upointer->getConfig().airObject.at(i.row());
        for(auto &el:secondListConfig.airObject)
            (el.targetNumber==myPath.targetNumber)?b=b&&false:b=b&&true;
        if(b){
            ui->listWidgetSecond->addItem(QString::number(myPath.targetNumber));
            secondListConfig.airObject.append(myPath);
            upointer->getScene()->setConf(secondListConfig);
            upointer->getScene()->deleteSceneItem();
            upointer->getScene()->drawPathAll();
        }}
}

void AdminForm::on_removeItem_clicked()
{   QModelIndex i=ui->listWidgetSecond->currentIndex();
    secondListConfig.airObject.removeAt(i.row());
    ui->listWidgetSecond->clear();
    for(auto &el:secondListConfig.airObject)
        ui->listWidgetSecond->addItem(QString::number(el.targetNumber));
    upointer->getScene()->setConf(secondListConfig);
    upointer->getScene()->deleteSceneItem();
    upointer->getScene()->drawPathAll();
}

void AdminForm::on_addAll_clicked()
{   ui->listWidgetSecond->clear();
    secondListConfig.airObject.clear();
    secondListConfig.airObject=upointer->getConfig().airObject;
    for(auto &el:secondListConfig.airObject)
        ui->listWidgetSecond->addItem(QString::number(el.targetNumber));
    upointer->getScene()->setConf(secondListConfig);
    upointer->getScene()->deleteSceneItem();
    upointer->getScene()->drawPathAll();
}

void AdminForm::on_removeAll_clicked()
{
    ui->listWidgetSecond->clear();
    secondListConfig.airObject.clear();
    upointer->getScene()->setConf(secondListConfig);
    upointer->getScene()->deleteSceneItem();
    upointer->getScene()->drawPathAll();
}

void AdminForm::on_play_clicked()
{    //сделать что бы при нажимании с экрана проподали пути и перезапускался налет
    upointer->setTrainingConf(secondListConfig);
    upointer->drawAir();
}


void AdminForm::on_saveFlying_clicked()
{
    QString str=QFileDialog::getSaveFileName(0,"Save Flying ", upointer->getConfDir()+"Flying","Object (*.ob);;All files (*.*)");
    if (str.isEmpty()) {
        return;
    }
    QFile file(str);
    if(file.open(QIODevice::WriteOnly)){
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_3);
        out << upointer->getConfig();
        QApplication::restoreOverrideCursor();
        file.close();
    }
}

void AdminForm::on_loadFlying_clicked()
{    QString str=QFileDialog::getOpenFileName(0,"Load Flying ",upointer->getConfDir(),"Object (*.ob);;All files (*.*)");
     if (str != "") {
         QFile file(str);
         if (!file.open(QIODevice::ReadOnly)) {
             QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
             return;
         }
         QDataStream in(&file);
         in.setVersion(QDataStream::Qt_5_3);
         QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
         iConfig newConfig;
         in>>newConfig;
         for(auto &el:upointer->getConfig().airObject)
             ui->numberPath->removeItem(0);
         upointer->setAirObjectConf(newConfig);
         for(auto &el:upointer->getConfig().airObject)
             ui->numberPath->addItem(QString::number(el.targetNumber),1);
         countTargetNumber=upointer->getConfig().airObject.size();
         loadTabTraining();
         file.close();
         upointer->save();
         QApplication::restoreOverrideCursor();
     }
}
