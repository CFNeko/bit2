#include "treewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TreeWidget w;
    w.show();

    return a.exec();
}
