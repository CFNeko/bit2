#include "mainwindow.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/table/table.qss");
    QString style;
    if (qss.open(QFile::ReadOnly))
    {
        style = QLatin1String(qss.readAll());

        qss.close();
    }

    QFile qssPg(":/pagenavigation/pagenavigation.qss");
    if (qssPg.open(QFile::ReadOnly))
    {
        style += QLatin1String(qssPg.readAll());

        qssPg.close();
    }

    a.setStyleSheet(style);

    MainWindow w;
    w.show();

    return a.exec();
}
