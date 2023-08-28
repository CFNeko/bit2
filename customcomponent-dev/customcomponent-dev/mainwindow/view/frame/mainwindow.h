#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool isLocked();
    void lockScreen();
    void retranslateUi();

protected:
    bool event(QEvent *event);

private:
    void initPage();

private slots:
    void slot_menuClicked(const QString& text);
    void slot_systemTrayClicked(QSystemTrayIcon::ActivationReason reason);
    void slot_menuAboutClicked();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon* m_pIconTray{ Q_NULLPTR };
    QMenu*      m_pMenuTry{ Q_NULLPTR };
    QAction*    m_pExit{ Q_NULLPTR };
    QAction*    m_pAbout{ Q_NULLPTR };


};

#endif // MAINWINDOW_H
