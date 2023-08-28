#ifndef MENU_DEFINS_H
#define MENU_DEFINS_H
#pragma once

#include <QString>
#include <QObject>
#include <QVariantList>

//为了方便后续进行中应为的切换，我们将定义切换成了类的形式

namespace menu {
class MenuDefines
{
public:

    static MenuDefines& instance()
    {
        static MenuDefines instance ;
        return instance;
    }

    const QString MAIN_TITLE = QObject::tr("Main Window");

    const QString MENU_SYSTEM_SET = QObject::tr("System Setting");
    const QString MENU_QUERY = QObject::tr("Query");
    const QString MENU_USER_MANAGER = QObject::tr("User Manage");
    const QString MENU_LOCK_SCREEN = QObject::tr("Lock Screen");
    const QString MENU_EXIT = QObject::tr("Quit");

    const QString MENU_CHANGE_PASSWD = QObject::tr("Edit Password");
    const QString MENU_LOGOUT = QObject::tr("Logout");

    const QString SUB_MENU_SYSTEM = QObject::tr("Setting");
    const QString SUB_MENU_STATION = QObject::tr("Station");

    const QString SUB_MENU_QUERY_LOG = QObject::tr("History Log");
    const QString SUB_MENU_QUERY_DATA = QObject::tr("History Data");

    const QString SUB_MENU_USER_GROUP = QObject::tr("Account Type");
    const QString SUB_MENU_USER = QObject::tr("Account");

    const QString CONTENT_MENU_ABOUT = QObject::tr("About");
    const QString CONTENT_MENU_EXIT_SHORT_CUT = QObject::tr("ctrl+w");

    QMap<QString, QVariantList> m_MenuMap;

private:

    MenuDefines()
    {
        QVariantList system, query, usermanager;

        system << SUB_MENU_STATION << SUB_MENU_SYSTEM << SUB_MENU_STATION << SUB_MENU_SYSTEM << SUB_MENU_STATION;
        query << SUB_MENU_QUERY_LOG << SUB_MENU_QUERY_DATA;
        usermanager << SUB_MENU_USER_GROUP << SUB_MENU_USER;
        m_MenuMap.insert(MENU_SYSTEM_SET, system);
        m_MenuMap.insert(MENU_QUERY, query);
        m_MenuMap.insert(MENU_USER_MANAGER, usermanager);
    }
};
}


#if 0
static const QString MAIN_TITLE(QObject::tr("Main Window"));

static const QString MENU_SYSTEM_SET(QObject::tr("System Setting"));
static const QString MENU_QUERY(QObject::tr("Query"));
static const QString MENU_USER_MANAGER(QObject::tr("User Manage"));
static const QString MENU_LOCK_SCREEN(QObject::tr("Lock Screen"));
static const QString MENU_EXIT(QObject::tr("Quit"));

static const QString MENU_CHANGE_PASSWD(QObject::tr("Edit Password"));
static const QString MENU_LOGOUT(QObject::tr("Logout"));

static const QString SUB_MENU_SYS_PARAM(QObject::tr("Setting"));
static const QString SUB_MENU_SYS_STATION(QObject::tr("Station"));

static const QString SUB_MENU_QUERY_LOG(QObject::tr("History Log"));
static const QString SUB_MENU_QUERY_DATA(QObject::tr("History Data"));

static const QString SUB_MENU_USER_GROUP(QObject::tr("Account Type"));
static const QString SUB_MENU_USER(QObject::tr("Account"));

static const QMap<QString, QVariantList> g_MenuMap
{
    {MENU_SYSTEM_SET, {SUB_MENU_SYS_PARAM, SUB_MENU_SYS_STATION}},
    {MENU_QUERY, {SUB_MENU_QUERY_LOG, SUB_MENU_QUERY_DATA}},
    {MENU_USER_MANAGER, {SUB_MENU_USER_GROUP, SUB_MENU_USER}}
};

#endif

#endif // MENU_DEFINS_H
