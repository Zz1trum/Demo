#ifndef USER_H
#define USER_H

#include <QDialog>

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void timeout();

private slots:
    void on_Return1_clicked();

    void on_infoBtn_clicked();

    void on_resetButton_clicked();

    void on_newpassBtn_clicked();

    void on_oldpassBtn_clicked();

    void on_newsButton_clicked();

    void on_clearBtn_clicked();

    void refreshBtn();
private:
    Ui::User *ui;
    QTimer *timer;
};

#endif // USER_H
