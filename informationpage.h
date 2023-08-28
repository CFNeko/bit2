#ifndef INFORMATIONPAGE_H
#define INFORMATIONPAGE_H

#include "userfriendlyitems.h"
#include "changepasswordpage.h"
#include "changedescriptionpage.h"
#include "changephonenumberpage.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtSql>

namespace Ui {
class InformationPage;
}

class InformationPage : public QWidget
{
    Q_OBJECT

public:
    explicit InformationPage(QWidget *parent = nullptr, int dno = 1);
    ~InformationPage();

private:
    Ui::InformationPage *ui;
    int *DoctorID;
};

#endif // INFORMATIONPAGE_H
