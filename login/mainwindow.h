#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "topup.h"
#include "user.h"
#include "sendtext.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void timeout();

private slots:
    void on_topupBtn_clicked();

    void on_userBtn_clicked();

    void on_sendBtn_clicked();

    void gettime();

private:
    Ui::MainWindow *ui;
    topUp topup;
    User auser;
    SendText asend;
    QTimer *qqtimer;
};

#endif // MAINWINDOW_H
