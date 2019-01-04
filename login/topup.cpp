#include "topup.h"
#include "ui_topup.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
double ed;
topUp::topUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topUp)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->topupLineEdit->setVisible(false);

}

topUp::~topUp()
{
    delete ui;
}


void topUp::on_Return_clicked()
{
    this->close();
    MainWindow *w;
    w=new MainWindow();
    w->show();
}

void topUp::on_huodongBtn_clicked()
{

    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(a);
    QString update_sql = QString("update user set exchange = exchange+6 where phone = %1 and huodong = 1").arg(a);
    QString hdover_sql = QString("update user set huodong = 0 where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString hd = sql_query.value(4).toString();
            if(hd=="1")
            {
                sql_query.exec(update_sql);
                sql_query.exec(hdover_sql);
                QMessageBox::information(this, "Congratulations", "You get 6 for free!  ", QMessageBox::Yes);
            }
            else
                QMessageBox::warning(this, "Warning", "You have participated in this activity!  ", QMessageBox::Ok);
        }

    }
}




void topUp::on_topup6Btn_pressed()
{
    ed=6;
    ui->topupLineEdit->setVisible(false);
    ui->topupLineEdit->clear();
}

void topUp::on_topup30Btn_pressed()
{
    ed=30;
    ui->topupLineEdit->setVisible(false);
    ui->topupLineEdit->clear();
}


void topUp::on_topup100Btn_pressed()
{
    ed=100;
    ui->topupLineEdit->setVisible(false);
    ui->topupLineEdit->clear();
}




void topUp::on_selfBtn_clicked()
{
    ui->getphoneLineEdit->setText(a);
}

void topUp::on_othersBtn_clicked()
{
    ui->getphoneLineEdit->clear();
    ui->getphoneLineEdit->setFocus();
}

void topUp::on_pushButton1_clicked()
{
    QString content=ui->getphoneLineEdit->text();
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(content);
    QString update_sql = QString("update user set exchange = exchange+%1 where phone = %2").arg(ed).arg(content);
    if (content=="")
        QMessageBox::warning(this, "Warning", "input the phone number!  ", QMessageBox::Ok);
    else if (content==a)
    {
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
                sql_query.exec(update_sql);
                QMessageBox::information(this, "Congratulations", "Top up for youself successfully!    ", QMessageBox::Yes);
        }
    }
    else
    {
        sql_query.exec(update_sql);
        QMessageBox::information(this, "Congratulations", "Top up for another successfully!    ", QMessageBox::Yes);
    }
}




void topUp::on_topupdfBtn_pressed()
{
    ui->topupLineEdit->setVisible(true);
    ui->topupLineEdit->setFocus();
    ui->topupdfBtn->setChecked(true);
}


void topUp::on_topupLineEdit_editingFinished()
{
   ed=(ui->topupLineEdit->text()).toDouble();
}

void topUp::mousePressEvent(QMouseEvent *event)
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
void topUp::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //移动窗体.
        this->move(m_windowPoint + relativePos );
    }
}
void topUp::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}
