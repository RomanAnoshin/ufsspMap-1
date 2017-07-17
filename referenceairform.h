#ifndef REFERENCEAIRFORM_H
#define REFERENCEAIRFORM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include <QImage>
#include <QTimer>
#include "airobject.h"

class ReferenceAirForm: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ReferenceAirForm(AirObject* ao, int number,bool isRef);
    ~ ReferenceAirForm();
    void inVisibility();
    void visibility(bool isV);
    void visibility2(bool b);
    // QGraphicsItem interface
    void advance(int phase) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int getOGP();
    bool getIsRefVisibilyty();
    QImage img;
public slots:
    void deleteItem();
    void timeOutSlot();

signals:
    void deleteInList(ReferenceAirForm* raf);

private:
    QString createStringTop();
    QString createStringBottom();
    void setImage();
    QString stringTop;
    QString stringBottom;
    int targetNumber;
    int count;
    AirObject* ao;
    bool isVisibility;
    bool isRefVisibilyty;


};

#endif // REFERENCEAIRFORM_H
