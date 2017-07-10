#ifndef AIROBJECT_H
#define AIROBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include "scenetypes.h"




class AirObject :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    AirObject(QObject *parent = 0);
    AirObject(float dx, float dy, qreal angle);
    AirObject(float dx, float dy, qreal angle, int x, int y, int w, int h );
    ~AirObject();
    void setMoveNumber(int i);
    void advance(int phase);
    void setFlightRote(flightRoute path);
    void setRectItem(int x, int y, int w, int h);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCount(int i);
    void setColor(QColor color);
    void setOGP(int i);
    int getOGP();
    void setSpeed(int speed);
    int getSpeed();
    void setHeightFly(int heightFly);
    int getHeightFly();
    void setIndex(int index);
    int getIndex();
    void setTypeObject(int typeObject);
    int getTypeObject();
    void setQuantity(int quantity);
    int getQuantity();
    void inVisibility();
    void setVisibility(bool b);
signals:
    void signalFinish(int count, flightRoute path, bool b, AirObject* ao);
    void signalDelete();

protected:
    QRectF boundingRect() const;

private:
    int moveNumber;
    int posX, posY, width, height;
    float dx;
    float dy;
    qreal angle;
    int count;
    int count2;
    flightRoute path;
    QColor color;
    int OGP;
    int speed;
    int heightFly;
    int index;
    int typeObject;
    int quantity;

    bool visibility;
};

#endif // AIROBJECT_H
