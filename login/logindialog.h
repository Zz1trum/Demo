#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include <QMouseEvent>
#include "register.h"

extern QString a;
extern bool m_move;
extern QPoint m_startPoint;
extern QPoint m_windowPoint;
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void mousePressEvent(QMouseEvent *event);//
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::LoginDialog *ui;

};

#endif // LOGINDIALOG_H
