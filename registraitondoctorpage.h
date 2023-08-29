#ifndef REGISTRAITONDOCTORPAGE_H
#define REGISTRAITONDOCTORPAGE_H

#include <QMouseEvent>
#include"listtemplate.h"
#include<QLineEdit>
#include<QComboBox>
#include<QTextEdit>
#include <QSqlDatabase>
#include <QPainter>
#include <QScrollArea>
#include "doctorpage.h"
#include "userfriendlyitems.h"
#include <QEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>


namespace Ui {
class RegistraitonDoctorPage;
}

class RegistraitonDoctorPage : public QWidget
{
    Q_OBJECT

public:
    explicit RegistraitonDoctorPage(QWidget *parent = nullptr, bool judge = false);
    ~RegistraitonDoctorPage();
    void paintEvent(QPaintEvent*) override;

private:
    Ui::RegistraitonDoctorPage *ui;
    bool isHistory;

signals:
    void rClosed();
protected:
    void closeEvent(QCloseEvent *event) override {
        emit rClosed();
        QWidget::closeEvent(event);
    }
};

#endif // REGISTRAITONDOCTORPAGE_H
