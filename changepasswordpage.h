#ifndef CHANGEPASSWORDPAGE_H
#define CHANGEPASSWORDPAGE_H

#include "userfriendlyitems.h"

#include <QWidget>
#include <QtSql>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

namespace Ui {
class ChangePasswordPage;
}

class ChangePasswordPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswordPage(QWidget *parent = nullptr, int dno = 1);
    ~ChangePasswordPage();

private:
    Ui::ChangePasswordPage *ui;
    int *DoctorID;
};

#endif // CHANGEPASSWORDPAGE_H
