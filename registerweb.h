#ifndef REGISTERWEB_H
#define REGISTERWEB_H

#include <QMainWindow>
#include"homepage.h"
#include"signup.h"
#include<QMessageBox>
#include <QMainWindow>
#include <QtDebug>
#include <QtSql>
#include <QFileInfo>
#include<QPainter>
#include<QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QMainWindow>
#include<QFormLayout>
#include<QRadioButton>
#include <QDebug>
#include <QSqlQuery>
#include<QButtonGroup>
#include "doctorpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWeb; }
QT_END_NAMESPACE

class RegisterWeb : public QMainWindow
{
    Q_OBJECT

public:
    RegisterWeb(QWidget *parent = nullptr);
    ~RegisterWeb();
    void paintEvent(QPaintEvent*);
     HomePage* homePage;
     DoctorPage *doctorpage;
     SignUp* signUp;

public slots:
     void on_exit_Signal_Received();
     void handleMessageBoxFinished(int result);
     void showMessageBox();


private:
    Ui::RegisterWeb *ui; 
    bool choice = false;
    QMessageBox* messageBox;
     QSqlDatabase myDB;
     void login();
};
#endif // REGISTERWEB_H
