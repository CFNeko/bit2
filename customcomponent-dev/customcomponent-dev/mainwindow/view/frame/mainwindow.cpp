#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "title_bar_widget.h"
#include "tab_cell_widget.h"
#include "menu_defines.h"
#include "globalapplication.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPage();
}

MainWindow::~MainWindow()
{
    m_pIconTray->deleteLater();
    m_pMenuTry->deleteLater();
    m_pExit->deleteLater();
    m_pAbout->deleteLater();
    delete ui;
}

void MainWindow::initPage()
{
    connect(ui->wdgTitle, &TitleBarWidget::signal_subMenuClicked, ui->wdgCell, &TabCellWidget::slot_subMenuClicked);
    connect(ui->wdgTitle, &TitleBarWidget::signal_nextsubMenuClicked, ui->wdgCell, &TabCellWidget::slot_nextsubMenuClicked);

    connect(ui->wdgTitle, &TitleBarWidget::signal_menuClicked, this, &MainWindow::slot_menuClicked);
    ui->wdgTitle->setCurrentPage(menu::MenuDefines::instance().MENU_SYSTEM_SET);

    app->setWindowInstance(this);

    m_pIconTray	= new QSystemTrayIcon(this);
    m_pIconTray->setIcon(QIcon(":/image/ic_bar_menu.png"));
    m_pIconTray->show();
    m_pIconTray->setToolTip("MainWindow v1.0");

    //托盘菜单
    m_pMenuTry = new QMenu(this);

    m_pAbout = m_pMenuTry->addAction(menu::MenuDefines::instance().CONTENT_MENU_ABOUT, this, SLOT(slot_menuAboutClicked()));
    m_pAbout->setData(menu::MenuDefines::instance().CONTENT_MENU_ABOUT);

    m_pMenuTry->addSeparator();
    m_pExit = m_pMenuTry->addAction(menu::MenuDefines::instance().MENU_EXIT, this, SLOT(close()));
    m_pExit->setData(menu::MenuDefines::instance().MENU_EXIT);
    m_pExit->setShortcut(menu::MenuDefines::instance().CONTENT_MENU_EXIT_SHORT_CUT);
    m_pExit->setIcon(QIcon(":/image/ic_bar_menu.png"));

    m_pIconTray->setContextMenu(m_pMenuTry);

    connect(m_pIconTray, &QSystemTrayIcon::activated, this, &MainWindow::slot_systemTrayClicked);
}

bool MainWindow::isLocked()
{
    return false;
}

void MainWindow::lockScreen()
{

}

void MainWindow::slot_menuClicked(const QString &text)
{
    if(menu::MenuDefines::instance().MENU_LOCK_SCREEN == text)
    {
        lockScreen();
        return;
    }
    if(menu::MenuDefines::instance().MENU_EXIT == text)
    {
        qApp->exit(0);
    }
}

void MainWindow::slot_systemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    {
        break;
    }
    case QSystemTrayIcon::DoubleClick:
    {

        break;
    }
    case QSystemTrayIcon::MiddleClick:
    {

        break;
    }

    default:
        break;
    }
}

void MainWindow::slot_menuAboutClicked()
{

}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);

        auto actions = m_pMenuTry->actions();
        for(const auto& action : actions)
		{
			action->setText(QApplication::translate("QObject", action->data().toString().toStdString().c_str(), Q_NULLPTR));
		}
    }

    return QWidget::event(event);
}
