#ifndef SENDTEXT_H
#define SENDTEXT_H

#include <QDialog>
#include <QMouseEvent>

extern QString StrCurrentTime;

namespace Ui {
class SendText;
}

class SendText : public QDialog
{
    Q_OBJECT

public:
    explicit SendText(QWidget *parent = nullptr);
    ~SendText();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void timeout();

private slots:
    void on_Return2_clicked();

    void on_sendtextBtn_clicked();

    void sendtime();

private:
    Ui::SendText *ui;
    QTimer *qtimer;
};

#endif // SENDTEXT_H
