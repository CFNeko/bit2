#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include<QMessageBox>
#include <QSqlDatabase>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

    void paintEvent(QPaintEvent *);
    void showSuccessMessageBox();
private slots:
    void on_pushButton_exit_clicked();


    void handleMessageBoxFinished(int result);
    void showMessageBox();
    void showFailMessageBox();
    void handleMessageFailBoxFinished(int result);

private:
    Ui::SignUp *ui;
    QMessageBox* messageBox;
    QSqlDatabase myDBregister;
signals:
    void signalToMain();
    void signalTologin();
};

#endif // SIGNUP_H
