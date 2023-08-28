#include "mainwindow.h"
#include "doctorpage.h"
#include "registerweb.h"
#include "registrationpage.h"
#include "recorditemtable.h"
#include "prescriptiontable.h"
#include "recorditemhistoryofdoctor.h"
#include "healthevaluation.h"

#include <QApplication>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("/home/user/Qtworks/qq_tiyanfu/database/database.db");
//    if (!db.open()) {
//        QMessageBox::critical(nullptr, "Error", "An error occurred: Fail to open database!");
//    }
//    qDebug() << "Database opened successfully";
    RegisterWeb *r = new RegisterWeb;
    r->show();
//    PrescriptionTable *p = new PrescriptionTable;
//    p->show();
//    RecordItemTable *r = new RecordItemTable;
//    r->show();
//    DoctorPage *d = new DoctorPage;
//    d->show();
//    RecordItemHistoryofDoctor *r = new RecordItemHistoryofDoctor;
//    r->show();
//    HealthEvaluation *h = new HealthEvaluation;
//    h->show();
    return a.exec();
}
