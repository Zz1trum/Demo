#ifndef TOPUP_H
#define TOPUP_H

#include <QWidget>
#include "logindialog.h"
#include <QLineEdit>

extern double ed;
namespace Ui {
class topUp;
}

class topUp : public QWidget
{
    Q_OBJECT

public:
    explicit topUp(QWidget *parent = nullptr);
    ~topUp();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_Return_clicked();


    void on_huodongBtn_clicked();


    void on_topup6Btn_pressed();


    void on_topup30Btn_pressed();


    void on_topup100Btn_pressed();


    void on_selfBtn_clicked();


    void on_othersBtn_clicked();


    void on_pushButton1_clicked();


    void on_topupdfBtn_pressed();


    void on_topupLineEdit_editingFinished();

private:
    Ui::topUp *ui;

};

#endif // TOPUP_H
