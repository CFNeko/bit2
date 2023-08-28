#include "registerweb.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegisterWeb w;
    w.show();
    return a.exec();
}
