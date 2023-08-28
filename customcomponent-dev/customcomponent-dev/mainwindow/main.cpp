#include "mainwindow.h"
#include "globalapplication.h"

#include <QFile>


int main(int argc, char *argv[])
{
    GlobalApplication a(argc, argv);
    QFile qss("../../CustomComponent/mainwindow/resource/main.qss");

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
