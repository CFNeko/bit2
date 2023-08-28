#include "widget.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QFile qss("../../CustomComponent/combobox/resource/main.qss");
    if (qss.open(QFile::ReadOnly))
    {
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qDebug() << style;
        qss.close();
    }

    w.show();

    return a.exec();
}
