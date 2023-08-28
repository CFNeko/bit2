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
     SignUp* signUp;
public slots:
     void on_exit_Signal_Received();
     void handleMessageBoxFinished(int result);
      void showMessageBox();


private:
    Ui::RegisterWeb *ui;
    void login();
     QMessageBox* messageBox;
     QSqlDatabase myDB;


};
#endif // REGISTERWEB_H
