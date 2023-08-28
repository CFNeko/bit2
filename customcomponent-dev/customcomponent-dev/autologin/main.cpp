#include "mainwindow.h"

#include "login_dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog dlg;

    if(dlg.exec() != QDialog::Accepted)
    {
        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
