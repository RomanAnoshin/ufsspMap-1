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

void ReferenceAirForm::inVisibility()
{   if(isRefVisibilyty){
        if(isVisibility)
            show();
        else
            hide();
    }
    else
        hide();
}

void ReferenceAirForm::visibility(bool isV)
{
    this->isRefVisibilyty=isV;
    inVisibility();
}

void ReferenceAirForm::visibility2()
{
    isVisibility=!isVisibility;
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
    painter->drawLine(-3,14,50,14);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

int ReferenceAirForm::getOGP()
{
    return ao->getOGP();
}

void ReferenceAirForm::deleteItem()
{
    deleteInList(this);
    delete this;
}

QString ReferenceAirForm::createStringTop()
{
    QString string1="";
    switch(ao->getIndex()){
    case 0:
        string1+=" |";
        break;
    case 1:
        string1+="В|";
        break;
    case 2:
        string1+="П|";
        break;
    case 3:
        string1+="з|";
        break;
    case 4:
        string1+="Р|";
        break;
    case 5:
        string1+="К|";
        break;
    case 6:
        string1+="с|";
        break;
    case 7:
        string1+="?|";
        break;
    default:
        string1+=" |";
        break;
    }
    switch (ao->getTypeObject()){
    case 0:
        string1+="И|";
        break;
    case 1:
        string1+="Б|";
        break;
    case 2:
        string1+="Ш|";
        break;
    default:
        string1+="И|";
        break;
    }
    string1+=QString::number(targetNumber/100)+QString::number((targetNumber%100)/10)+QString::number(targetNumber%10)+"|";
    string1+="т";
    return string1;
}

QString ReferenceAirForm::createStringBottom()
{
    QString string2="";
    string2+=QString::number(ao->getHeightFly()/100)+QString::number((ao->getHeightFly()%100)/10)+QString::number(ao->getHeightFly()%10)+" |";
    string2+=QString::number(ao->getSpeed()/1000)+QString::number((ao->getSpeed()%1000)/100)+QString::number((ao->getSpeed()%100)/10)+QString::number(ao->getSpeed()%10);
    return string2;
}



