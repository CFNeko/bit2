#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include "userfriendlyitems.h"
#include <QWidget>
#include <QFrame>
#include <QTableWidget>

namespace Ui {
class RegistrationPage;
}

class RegistrationPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationPage(QWidget *parent = nullptr, int dno = 1);
    ~RegistrationPage() {};

private:
    Ui::RegistrationPage *ui;
    int *DoctorID;
    int *PatientID;

    QTableWidget  *registrationTable = new QTableWidget();

};

#endif // REGISTRATIONPAGE_H
