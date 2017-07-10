#ifndef TARGETNUMBER_H
#define TARGETNUMBER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "airobject.h"
#include "scenetypes.h"


class TargetNumber:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    TargetNumber(QString number,float dx, float dy);
    // QGraphicsItem interface
    void advance(int phase) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void inVisibility();
    void setVisibility(bool b);
    void setOGP(int i);
    int getOGP();
signals:
    void deleteInList(TargetNumber* tn);
public slots:
    void deleteItem();
private:
    QString s;
    float dx,dy;
    int count;
    bool visibility;
    int OGP;
};

#endif // TARGETNUMBER_H
