#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPointF>

#include "moveitem.h"
#include "scenetypes.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);
    ~GraphicsScene();

    void drawLinePath();
    void setIsCreatePath(bool b);
    void setIsCreate(bool b);
    void createItem(QPointF point);
    void setPath(flightRoute path);
    void setOGP(int i);
    void setTypeAirObject(int i);
    void setSpeed(int speed);
    void setHeightFly(int heightFly);
    void setIndex(int index);
    void setQuantity(int quantity);
    flightRoute getPath();
    void deleteSceneItem();
    void drawPath();
    void drawPathAll();
    int selectInNumberPathPoint;
    void setConf(iConfig conf);

private:
        QList<MoveItem*>moveItemInScene;
        QList<QGraphicsLineItem*>line;
        flightRoute path;
        bool isCreatePath;
        bool isCreate;
        iConfig conf;

signals:
    //сигнал для передачи положения курсора
    void signalCursor(QPointF point);
    void signalMousePress(QPointF point);
    void signalMouseTracking(bool isTracing);
    void signalCreateNewPathPoint();


    // QGraphicsScene interface
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GRAPHICSSCENE_H
