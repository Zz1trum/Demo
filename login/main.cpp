#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog dlg;

    //使用绝对路径打开qss文件
    QFile qss("D:/Qt/login/style.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qDebug("Open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else
    {
        qDebug("Open failed");
    }

   if (dlg.exec() == QDialog::Accepted)
   {
       w.show();
       return a.exec();
   }
       else return 0;
}
