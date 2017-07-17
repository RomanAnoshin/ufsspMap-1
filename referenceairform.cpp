#include "referenceairform.h"
#include <iostream>


ReferenceAirForm::ReferenceAirForm(AirObject *ao, int number,bool isRef): QObject(), QGraphicsItem()
{
    count=0;
    this->ao=ao;
    this->targetNumber=number;
    isVisibility=(ao->getVisibility());
    isRefVisibilyty=isRef;
    inVisibility();

}

ReferenceAirForm::~ReferenceAirForm()
{
}

void ReferenceAirForm::inVisibility()
{   if(isRefVisibilyty&&isVisibility)
        show();
   else
        hide();
}

void ReferenceAirForm::visibility(bool isV)
{
    this->isRefVisibilyty=isV;
    inVisibility();
}

void ReferenceAirForm::visibility2(bool b)
{
    isVisibility=b;
    inVisibility();
}

void ReferenceAirForm::advance(int phase)
{
    if(phase){
        if(((++count)%5)==0)
            moveBy(ao->getDx()*10,ao->getDy()*10);
    }

}

QRectF ReferenceAirForm::boundingRect() const
{
    return QRectF(0,0,70,30);
}

void ReferenceAirForm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(ao->getColor());
    painter->drawText(QRect(0,0,70,30),createStringTop());
    painter->drawText(QRect(0,13,70,30),createStringBottom());
    setImage();
    painter->drawImage(7,0,img);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int ReferenceAirForm::getOGP()
{
    return ao->getOGP();
}

bool ReferenceAirForm::getIsRefVisibilyty()
{

}

void ReferenceAirForm::deleteItem()
{
    deleteInList(this);
    delete this;
}

void ReferenceAirForm::timeOutSlot()
{
    isRefVisibilyty=false;
    inVisibility();
}

QString ReferenceAirForm::createStringTop()
{
    QString string1="";
    switch(ao->getIndex()){
    case 0:
        string1+="   ";
        break;
    case 1:
        string1+="В ";
        break;
    case 2:
        string1+="П ";
        break;
    case 3:
        string1+="з ";
        break;
    case 4:
        string1+="Р ";
        break;
    case 5:
        string1+="К ";
        break;
    case 6:
        string1+="с ";
        break;
    case 7:
        string1+="? ";
        break;
    default:
        string1+="   ";
        break;
    }
    switch (ao->getTypeObject()){
    case 0:
        string1+="     ";
        break;
    case 1:
        string1+="     ";
        break;
    case 2:
        string1+="     ";
        break;
    default:
        string1+="     ";
        break;
    }
    string1+=QString::number(targetNumber/100)+QString::number((targetNumber%100)/10)+QString::number(targetNumber%10)+"";
    return string1;
}

QString ReferenceAirForm::createStringBottom()
{
    QString string2="";
    string2+=QString::number(ao->getHeightFly()/100)+QString::number((ao->getHeightFly()%100)/10)+QString::number(ao->getHeightFly()%10)+"-";
    string2+=QString::number(ao->getSpeed()/1000)+QString::number((ao->getSpeed()%1000)/100)+QString::number((ao->getSpeed()%100)/10)+QString::number(ao->getSpeed()%10);
    return string2;
}

void ReferenceAirForm::setImage()
{
    if(ao->getOGP()==0){
        if(ao->getTypeObject()==0){
           img=QImage(":/MyImage/classVO/aGreen.png");
        }
       else if (ao->getTypeObject()==1){
           img=QImage(":/MyImage/classVO/rGreen.png");
        }
        if(ao->getTypeObject()==2){
           img=QImage(":/MyImage/classVO/vGreen.png");
        }
        if(ao->getTypeObject()==3){
           img=QImage(":/MyImage/classVO/sGreen.png");
        }
    }
   else if(ao->getOGP()==1){
        if(ao->getTypeObject()==0){
           img=QImage(":/MyImage/classVO/aRed.png");
        }
        if(ao->getTypeObject()==1){
           img=QImage(":/MyImage/classVO/rRed.png");
        }
        if(ao->getTypeObject()==2){
           img=QImage(":/MyImage/classVO/vRed.png");
        }
        if(ao->getTypeObject()==3){
           img=QImage(":/MyImage/classVO/sRed.png");
        }
    }
    else if(ao->getOGP()==2){
        if(ao->getTypeObject()==0){
           img=QImage(":/MyImage/classVO/aGray.png");
        }
        if(ao->getTypeObject()==1){
           img=QImage(":/MyImage/classVO/rGray.png");
        }
        if(ao->getTypeObject()==2){
           img=QImage(":/MyImage/classVO/vGray.png");
        }
        if(ao->getTypeObject()==3){
           img=QImage(":/MyImage/classVO/sGray.png");
        }
    }
    else
        img=QImage(":/MyImage/classVO/aGreen.png");
}



