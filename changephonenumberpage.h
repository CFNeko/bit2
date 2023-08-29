#ifndef CHANGEPHONENUMBERPAGE_H
#define CHANGEPHONENUMBERPAGE_H

#include <QWidget>
#include <QtSql>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>

#include "userfriendlyitems.h"

namespace Ui {
class ChangePhoneNumberPage;
}

class ChangePhoneNumberPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePhoneNumberPage(QWidget *parent = nullptr, int dno = 1);
    ~ChangePhoneNumberPage();

private:
    Ui::ChangePhoneNumberPage *ui;
    int *DoctorID;
};

#endif // CHANGEPHONENUMBERPAGE_H
