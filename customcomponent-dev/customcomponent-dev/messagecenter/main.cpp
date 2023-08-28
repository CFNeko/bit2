#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("../../CustomComponent/messagecenter/image/main.qss");

    if (qss.open(QFile::ReadOnly))
    {
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
