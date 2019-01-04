#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    qqtimer = new QTimer(this);
    connect(qqtimer, SIGNAL(timeout()), this, SLOT(gettime()));
    qqtimer->start(1000);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_topupBtn_clicked()
{
    this->close();
    topup.show();
}

void MainWindow::on_userBtn_clicked()
{
    this->close();
    auser.exec();
}

void MainWindow::on_sendBtn_clicked()
{
    this->close();
    asend.exec();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
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
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //移动窗体.
        this->move(m_windowPoint + relativePos );
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}
void MainWindow::gettime()
{
    QDateTime current_time = QDateTime::currentDateTime();
    //显示时间，格式为：年-月-日 时：分：秒 周几
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->label_CurrentTime->setText(StrCurrentTime);
}



