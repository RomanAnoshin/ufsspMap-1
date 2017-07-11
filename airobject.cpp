#include "airobject.h"


AirObject::AirObject(QObject *parent): QObject(parent), QGraphicsItem()
{
    dx=2;
    dy=2;
    count=0;
    count2=0;
    moveNumber=0;
    color=QColor(Qt::white);
    visibility=true;
    setOGP(0);
    setSpeed(1000);
    setHeightFly(100);
    setIndex(0);
    setTypeObject(0);
    setQuantity(1);
}

AirObject::AirObject(float dx, float dy, qreal angle): AirObject()
{   this->angle=angle;
    this->dx=dx;
    this->dy=dy;
    posX = -5;
    posY = -5;
    width = 10;
    height = 10;
    setRotation(angle);
}

AirObject::AirObject(float dx, float dy,qreal angle,int x, int y, int w, int h) : AirObject(dx,dy,angle)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

AirObject::~AirObject()
{
}

void AirObject::setMoveNumber(int i)
{
    this->moveNumber=i;
}

QRectF AirObject::boundingRect() const
{
    return QRectF(posX,posY,width,height);   // Ограничиваем область, в которой воздушный объект
}

void AirObject::advance(int phase)
{   if(phase){
        if(count==moveNumber){
            signalFinish(path.count, path, visibility,this);
            signalDelete();

            delete this;
            return;
        }
        if(((++count)%5)==0){
            moveBy(dx*10,dy*10);
        }
    }}

void AirObject::setFlightRote(flightRoute path)
{
    this->path=path;
}

void AirObject::setRectItem(int x, int y, int w, int h)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

void AirObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color);
    painter->setPen(color);
    QRect r(-2,-2,4,4);
    painter->drawEllipse(r);
    painter->drawLine(0,0,0,-10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void AirObject::setCount(int i)
{
    this->count2=i;
}

void AirObject::setColor(QColor color)
{
    this->color=color;
}

QColor AirObject::getColor()
{
    return this->color;
}

void AirObject::setOGP(int i)
{
    this->OGP=i;
}

int AirObject::getOGP()
{
    return OGP;
}

void AirObject::setSpeed(int speed)
{
    this->speed=speed;
}

int AirObject::getSpeed()
{
    return this->speed;
}

void AirObject::setHeightFly(int heightFly)
{
    this->heightFly=heightFly;
}

int AirObject::getHeightFly()
{
    return this->heightFly;
}

void AirObject::setIndex(int index)
{
    this->index=index;
}

int AirObject::getIndex()
{
    return this->index;
}

void AirObject::setTypeObject(int typeObject)
{
    this->typeObject=typeObject;
}

int AirObject::getTypeObject()
{
    return this->typeObject;
}

void AirObject::setQuantity(int quantity)
{
    this->quantity=quantity;
}

int AirObject::getQuantity()
{
    return this->quantity;
}

void AirObject::inVisibility()
{
    visibility=!visibility;
    if(visibility)
        show();
    else
        hide();
}

void AirObject::setVisibility(bool b)
{
    this->visibility=!b;
    inVisibility();
}

float AirObject::getDx()
{
    return this->dx;
}

float AirObject::getDy()
{
    return this->dy;
}

bool AirObject::getVisibility()
{
    return this->visibility;
}
