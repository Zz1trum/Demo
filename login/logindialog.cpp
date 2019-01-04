#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
#include <QString>
#include <QtSql>

QString a;
bool m_move;
QPoint m_startPoint;
QPoint m_windowPoint;
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    m_move = false;
    this->setWindowFlags(Qt::FramelessWindowHint);

    //打开SQLite
    QSqlDatabase database;
    if (QSqlDatabase::contains("sq"))
    {
        database = QSqlDatabase::database("sq");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("User.db");
        database.setUserName("root");
        database.setPassword("123456");
    }
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else//Sql操作
    {
        QSqlQuery sql_query;
        QString create_sql = "create table user (phone varchar(11), password varchar(16), name varchar(20), exchange float, huodong int, text char(100))";
        sql_query.prepare(create_sql);
        if(!sql_query.exec())
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString iphone=ui->userLineEdit->text();
    QString ipassword=ui->pwdLineEdit->text();
    QSqlQuery sql_query;
    QVariant spassword;
    QString select_sql = "select * from user";
    if(!sql_query.exec(select_sql))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        bool flag=true;
        while(sql_query.next())
        {
            QString phone = sql_query.value(0).toString();
            QString password = sql_query.value(1).toString();
            QString name = sql_query.value(2).toString();
            QString exchange = sql_query.value(3).toString();
            QString huodong = sql_query.value(4).toString();
            QString text = sql_query.value(5).toString();
            qDebug()<<QString("phone:%1    password:%2    name:%3    exchange:%4    hd:%5    text:%6").arg(phone).arg(password).arg(name).arg(exchange).arg(huodong).arg(text);
            if(ipassword==password&&iphone==phone)
            {
               accept();

               a=iphone;

               flag=false;
            }
        }
        if(flag)
        {
           QMessageBox message(QMessageBox::NoIcon, "Warning","");
           message.setIconPixmap(QPixmap("D:/Qt/login/Warning.png").scaled(300,200));
           message.exec();
           ui->userLineEdit->clear();
           ui->pwdLineEdit->clear();
           ui->userLineEdit->setFocus();
        }
    }
}


void LoginDialog::on_registerBtn_clicked()
{
    Register reg;
    reg.exec();
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
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
void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //移动窗体.
        this->move(m_windowPoint + relativePos );
    }
}
void LoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}




