#ifndef CHANGEDESCRIPTIONPAGE_H
#define CHANGEDESCRIPTIONPAGE_H

#include <QWidget>
#include <QtSql>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>

#include "userfriendlyitems.h"

namespace Ui {
class ChangeDescriptionPage;
}

class ChangeDescriptionPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeDescriptionPage(QWidget *parent = nullptr, int dno = 1);
    ~ChangeDescriptionPage();

private:
    Ui::ChangeDescriptionPage *ui;
    int *DoctorID;
};

#endif // CHANGEDESCRIPTIONPAGE_H
