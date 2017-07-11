#ifndef REFERENCEAIRFORM_H
#define REFERENCEAIRFORM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include "airobject.h"

class ReferenceAirForm: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ReferenceAirForm(AirObject* ao, int number,bool isRef);
    void inVisibility();
    void visibility(bool isV);
    void visibility2();
    // QGraphicsItem interface
    void advance(int phase) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int getOGP();

public slots:
    void deleteItem();

signals:
    void deleteInList(ReferenceAirForm* raf);

private:
    QString createStringTop();
    QString createStringBottom();
    QString stringTop;
    QString stringBottom;
    int targetNumber;
    int count;
    AirObject* ao;
    bool isVisibility;
    bool isRefVisibilyty;
};

#endif // REFERENCEAIRFORM_H
