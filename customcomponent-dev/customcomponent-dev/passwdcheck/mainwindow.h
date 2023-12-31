#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_passwdChanged(const QString &value);
    void slot_cpasswdChanged(const QString &value);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
