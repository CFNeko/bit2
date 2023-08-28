#include "title_bar_widget.h"
#include "ui_title_bar_widget.h"

#include "menu_defines.h"
#include "globalapplication.h"

using namespace menu;
TitleBarWidget::TitleBarWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TitleBarWidget)
{
    ui->setupUi(this);
    initPage();
}

TitleBarWidget::~TitleBarWidget()
{
    delete m_pCurrentUser;
    m_pCurrentUser = Q_NULLPTR;

    delete m_pMainMenu;
    m_pMainMenu = Q_NULLPTR;

    delete m_pUserMenu;
    m_pUserMenu = Q_NULLPTR;

    delete m_pLockScreen;
    m_pLockScreen = Q_NULLPTR;

    delete m_pQuit;
    m_pQuit = Q_NULLPTR;

    delete ui;
}

void TitleBarWidget::initPage()
{
    m_pMainMenu = new QMenu(this);
    ui->btnMenu->setMenu(m_pMainMenu);

    auto system = m_pMainMenu->addAction(MenuDefines::instance().MENU_SYSTEM_SET, this, SLOT(slot_menuClicked()));
    system->setData(MenuDefines::instance().MENU_SYSTEM_SET);
    auto query = m_pMainMenu->addAction(MenuDefines::instance().MENU_QUERY, this, SLOT(slot_menuClicked()));
    query->setData(MenuDefines::instance().MENU_QUERY);
    auto usermanager = m_pMainMenu->addAction(MenuDefines::instance().MENU_USER_MANAGER, this, SLOT(slot_menuClicked()));
    usermanager->setData(MenuDefines::instance().MENU_USER_MANAGER);

    m_pMainMenu->addSeparator();
    m_pLockScreen = m_pMainMenu->addAction(MenuDefines::instance().MENU_LOCK_SCREEN, this, SLOT(slot_menuClicked()));
    m_pLockScreen->setData(MenuDefines::instance().MENU_LOCK_SCREEN);
    m_pMainMenu->addSeparator();

    m_pQuit = m_pMainMenu->addAction(MenuDefines::instance().MENU_EXIT, this, SLOT(slot_menuClicked()));
    m_pQuit->setData(MenuDefines::instance().MENU_EXIT);

    m_pUserMenu = new QMenu(this);
    ui->btnUser->setMenu(m_pUserMenu);

    m_pCurrentUser = new QAction();
    m_pUserMenu->addAction(m_pCurrentUser);
    auto changepassd = m_pUserMenu->addAction(MenuDefines::instance().MENU_CHANGE_PASSWD, this, SLOT(slot_userMenuClicked()));
    changepassd->setData(MenuDefines::instance().MENU_CHANGE_PASSWD);
    auto logout = m_pUserMenu->addAction(MenuDefines::instance().MENU_LOGOUT, this, SLOT(slot_userMenuClicked()));
    logout->setData(MenuDefines::instance().MENU_LOGOUT);

    QString text = QApplication::translate("Qbject", MenuDefines::instance().MAIN_TITLE.toStdString().c_str(), Q_NULLPTR);
    ui->lbTitle->setText(text);
    connect(ui->subMenu, &MenuBarWidget::signal_subMenuClicked, this, &TitleBarWidget::signal_subMenuClicked);
    connect(ui->subMenu, &MenuBarWidget::signal_nextSubMenuClicked, this, &TitleBarWidget::signal_nextsubMenuClicked);

    connect(ui->btnMin, &QPushButton::clicked, this, &TitleBarWidget::on_btnMinClicked);
    connect(ui->btnMax, &QPushButton::clicked, this, &TitleBarWidget::on_btnMaxClicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &TitleBarWidget::on_btnCloseClicked);
}

void TitleBarWidget::slot_menuClicked()
{
    auto pAction = qobject_cast<QAction*>(QObject::sender());
    if (Q_NULLPTR == pAction)
    {
        return;
    }

    if (pAction == m_pLockScreen || pAction == m_pQuit)
    {
        //锁屏或者退出时给主界面发消息
        emit signal_menuClicked(pAction->text());
        return;
    }

    ui->subMenu->setCurrentPage(pAction->text());
}

void TitleBarWidget::slot_userMenuClicked()
{
    auto pAction = qobject_cast<QAction *>(QObject::sender());
    if (Q_NULLPTR == pAction)
    {
        return;
    }
    emit signal_menuClicked(pAction->text());
}

void TitleBarWidget::on_btnMinClicked()
{
    app->getMainWindow()->showMinimized();
}

void TitleBarWidget::on_btnMaxClicked()
{
   if(ui->btnMax->isChecked())
   {
       app->getMainWindow()->showFullScreen();
       return;
   }
   app->getMainWindow()->showNormal();
}

void TitleBarWidget::on_btnCloseClicked()
{
    app->exit(0);
}

void TitleBarWidget::setCurrentUser(const QString &user)
{
    m_pCurrentUser->setText(user);
}

QString TitleBarWidget::getCurrentUser() const
{
    return m_pCurrentUser->text();
}
void TitleBarWidget::setCurrentPage(const QString &page)
{
    ui->subMenu->setCurrentPage(page);
}

bool TitleBarWidget::event(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);

        auto actions = ui->btnMenu->menu()->actions();
        for(const auto& action : actions)
        {
            action->setText(QApplication::translate("QObject", action->data().toString().toStdString().c_str(), Q_NULLPTR));
        }

        auto users = ui->btnMenu->menu()->actions();
        for(const auto& action : users)
        {
            action->setText(QApplication::translate("QObject", action->data().toString().toStdString().c_str(), Q_NULLPTR));
        }

        ui->lbTitle->setText(QApplication::translate("Qbject", MenuDefines::instance().MAIN_TITLE.toStdString().c_str(), Q_NULLPTR));
    }

    return QWidget::event(event);
}
