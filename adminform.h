#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include "upointer.h"

namespace Ui {
class AdminForm;
}

class AdminForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminForm(QWidget *parent = 0);
    ~AdminForm();
    void setPointer(UPointer *up);

private slots:
    void on_bgImg_clicked();

    void on_addLine_clicked();

    void on_x0_valueChanged(double arg1);

    void on_y0_valueChanged(double arg1);

    void on_x1_valueChanged(double arg1);

    void on_y1_valueChanged(double arg1);

private:
    Ui::AdminForm *ui;
    UPointer *upointer;
    bool lockPoint;
};

#endif // ADMINFORM_H
