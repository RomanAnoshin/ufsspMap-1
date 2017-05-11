#ifndef UPOINTER_H
#define UPOINTER_H

#include <QObject>
#include <QGraphicsScene>
#include "scenetypes.h"

class UPointer : public QObject
{
    Q_OBJECT
public:
    explicit UPointer(QString mainConfDir, QObject *parent = 0);
    void reWrite(int width, int height);
    QGraphicsScene * getScene();
    QString getConfDir();
    void setBg(QString bg);
    QString getBg();
    void setPoint(QPoint qp);
    void createLine(iDataLines *dlines);
    void setPosition(float x0,float y0,float x1,float y1);
    fPoint getzPosition();
    fPoint getlastPosition();

signals:

public slots:

private:
    QPixmap     pic;
    QGraphicsScene *scene;
    void reLoad();
    void save();
    iConfig conf;
    QList <int> groupList;
    void loadGroup(int groupNumber);
    void addLine(iDataLines line);
    void addImg(iDataImages image);
    int imgWidth;
    int imgHeight;
    iPoint mainPosition;

    fPoint toCoord(iPoint position);
    iPoint fromCoord(fPoint position);
    QString confdir;
    bool isEditLine;
    bool isEditImg;
    iDataLines *dl;
    iDataImages *di;
};

#endif // UPOINTER_H
