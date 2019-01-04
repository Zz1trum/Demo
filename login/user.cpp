#include "user.h"
#include "ui_user.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QtSql>
#include <QDebug>


User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_infoBtn_clicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshBtn()));
    timer->start(1000);
    ui->resetLabel1->setVisible(false);
    ui->resetLabel2->setVisible(false);
    ui->resetLineEdit1->setVisible(false);
    ui->resetLineEdit2->setVisible(false);
    ui->newpassBtn->setVisible(false);
    ui->oldpassBtn->setVisible(false);
    ui->clearBtn->setVisible(false);
}

User::~User()
{
    delete ui;
}

void User::on_Return1_clicked()
{
    this->close();
    MainWindow *w;
    w = new MainWindow();
    w->show();
}

void User::on_infoBtn_clicked()
{
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
        QString name = sql_query.value(2).toString();
        QString account = sql_query.value(3).toString();
        ui->nameshowLabel->setText(name);
        ui->accountshowLabel->setText(account);
        }
    }
}

void User::mousePressEvent(QMouseEvent *event)
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
void User::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //移动窗体.
        this->move(m_windowPoint + relativePos );
    }
}
void User::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}


void User::on_resetButton_clicked()
{
    ui->resetLabel1->setVisible(true);
    ui->resetLabel2->setVisible(true);
    ui->resetLineEdit1->setVisible(true);
    ui->resetLineEdit2->setVisible(true);
    ui->newpassBtn->setVisible(true);
    ui->oldpassBtn->setVisible(true);
    ui->resetLineEdit1->setFocus();
}


void User::on_newpassBtn_clicked()
{
    ui->resetButton->setVisible(false);
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString oldpass = sql_query.value(2).toString();
            QString ioldpass = ui->resetLineEdit1->text();
            QString inewpass = ui->resetLineEdit2->text();
            QString update_sql = QString("update user set password = %1 where phone = %2").arg(inewpass).arg(a);
            qDebug()<<oldpass;
            if(ioldpass!=oldpass)
            {
                QMessageBox::warning(this, "Warning", "The old password is wrong!   ", QMessageBox::Ok);
                ui->resetLineEdit1->clear();
            }
            else
            {
                sql_query.exec(update_sql);
                QMessageBox::warning(this, "Warning", "You have reset your password!   ", QMessageBox::Ok);
                ui->resetLabel1->setVisible(false);
                ui->resetLabel2->setVisible(false);
                ui->resetLineEdit1->setVisible(false);
                ui->resetLineEdit2->setVisible(false);
                ui->newpassBtn->setVisible(false);
                ui->oldpassBtn->setVisible(false);
            }
        }
    }
}


void User::on_oldpassBtn_clicked()
{
    ui->resetLabel1->setVisible(false);
    ui->resetLabel2->setVisible(false);
    ui->resetLineEdit1->setVisible(false);
    ui->resetLineEdit2->setVisible(false);
    ui->newpassBtn->setVisible(false);
    ui->oldpassBtn->setVisible(false);
}

void User::on_newsButton_clicked()
{
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString text = sql_query.value(5).toString();
            if(text=="")
            {
                QMessageBox::warning(this, "Warning", "No new message!  ", QMessageBox::Ok);
            }
            else {
                QStringList info = text.split("|");
                QString a = info[0];//收信者
                QString b = info[1];//内容
                QString c = info[2];//发送者
                QString d = info[3];//时间
                QString total = c+" send a message to you :\n"+b+"\n"+d;
                ui->messagehere->setText(total);
                ui->clearBtn->setVisible(true);
            }
        }
    }
}

void User::on_clearBtn_clicked()
{
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(a);
    QString update_sql = QString("update user set text =:text where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            sql_query.prepare(update_sql);
            sql_query.bindValue(":text","");
            sql_query.exec();
        }
    }
    ui->messagehere->setText("");
    ui->clearBtn->setVisible(false);
    QMessageBox::warning(this, "Warning", "Message has been cleared!  ", QMessageBox::Ok);
}

void User::refreshBtn()
{
    QSqlQuery sql_query;
    QString select_sql = QString("select * from user where phone = %1").arg(a);
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString text = sql_query.value(5).toString();
            if(text!="")
            {
                ui->newsButton->setStyleSheet("QPushButton{color:red}");
                ui->newsButton->setText("NEW!!");
            }
            else
            {
                ui->newsButton->setText("Message");
                ui->newsButton->setStyleSheet("QPushButton{color:black}");
            }
        }
    }
}
