#include "datetime.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DateTime w;
    w.show();

    return a.exec();
}
