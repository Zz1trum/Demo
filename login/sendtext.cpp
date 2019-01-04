#include "sendtext.h"
#include "ui_sendtext.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

QString StrCurrentTime;
SendText::SendText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendText)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    qtimer = new QTimer(this);
    connect(qtimer, SIGNAL(timeout()), this, SLOT(sendtime()));
    qtimer->start(100000);
}

SendText::~SendText()
{
    delete ui;
}

void SendText::on_Return2_clicked()
{
    this->close();
    MainWindow *w;
    w = new MainWindow();
    w->show();
}

void SendText::on_sendtextBtn_clicked()
{

    QString t1 = ui->t1LineEdit->text();
    QString t2 = ui->t2PlainTextEdit->document()->toPlainText();
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(t1);
    QString select_sql2 = QString("select * from user where phone = %1").arg(a);
    QString sign = "|";
    QString t = t1+sign+t2+sign+QString(a)+sign+StrCurrentTime;
    QString update_sql = QString("update user set text = :text where phone = %1").arg(t1);
    QString update_sql2 = QString("update user set exchange=exchange-1 where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while (sql_query.next())
        {
            sql_query.prepare(update_sql);
            sql_query.bindValue(":text",t);
            sql_query.exec();
        }
        QMessageBox::information(this, "Congratulations", "Send Successfully!  ", QMessageBox::Yes);
        sql_query.exec(update_sql2);
    }
}

void SendText::sendtime()
{
    QDateTime current_time = QDateTime::currentDateTime();
    StrCurrentTime = current_time.toString("MM-dd hh:mm:ss");
}

void SendText::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void SendText::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //移动窗体.
        this->move(m_windowPoint + relativePos );
    }
}
void SendText::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}
