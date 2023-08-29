#include "registerweb.h"

#include <QApplication>
#include "doctorpage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegisterWeb w;
    w.show();
    //HomePage w;
    //w.show();
    //DoctorPage *d = new DoctorPage;
    //d->show();
    return a.exec();
}
