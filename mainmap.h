#ifndef MAINMAP_H
#define MAINMAP_H

#include <QMainWindow>
#include <QDateTime>
#include <QMenu>
#include <QAction>
#include "upointer.h"
#include "scenetypes.h"
#include "adminform.h"
#include <QMouseEvent>

namespace Ui {
class MainMap;
}

class MainMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMap(QWidget *parent = 0);
    ~MainMap();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *mouse) override;

public slots:
    void slotDisplay(QPointF point);

private slots:
    void on_btnRG_clicked();
    void setDateTime();
    void on_pushButton_31_clicked();

    void testSlot(QString s);
    void focusSlot();

private:
    Ui::MainMap *ui;
    UPointer *upointer;
    AdminForm *admin;
    void setSubButtonStYle();
    QMenu *createStaticMenu();
    QMenu *createSelParMenu();
    QMenu *createDisplayMenu();
    //------------------------
    // поменять имя
    QMenu *createResetMenu();
    //------------------------
    QTimer *focusTimer;
    bool word1;
    bool word2;
    bool word3;
    bool wordSelection;
    bool wordRef1;
    bool wordRef2;
    void parseMyString(QString s);
};

#endif // MAINMAP_H
