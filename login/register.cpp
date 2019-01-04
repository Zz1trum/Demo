#include "register.h"
#include "ui_register.h"
#include <QString>
#include <QMessageBox>
#include <QtSql>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground, true);//透明化窗体
}

Register::~Register()
{
    delete ui;
}

void Register::on_OKBtn_clicked()
{
    QString phone=ui->phoneLineEdit->text();
    QString password=ui->pwLineEdit->text();
    QString name=ui->nameLineEdit->text();
    QString exchange="0";
    QString huodong="1";
    QString text="";
    if((phone.isEmpty())||(password.isEmpty())||(name.isEmpty()))
    {
        QMessageBox::warning(this, "", "Wrong!  ", QMessageBox::Ok);
    }
    else
    {
        QString zc=QString("insert into user values ('%1','%2','%3','%4','%5','%6'); ").arg(phone).arg(password).arg(name).arg(exchange).arg(huodong).arg(text);
        QSqlQuery sql_query;
        if(sql_query.exec(zc))
        {
            QMessageBox::information(this, "", "Success!   ", QMessageBox::Yes);
        }
        else {
            qDebug() << "Register failed" << sql_query.lastError();
        }
    }
    this->hide();
}
