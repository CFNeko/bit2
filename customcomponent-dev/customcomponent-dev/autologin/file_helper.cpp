#include "file_helper.h"

#include <QCoreApplication>
#include <QSettings>

#define LOAD_CFG_VARIANT(x)     cfg.value(x)
#define SAVE_CFG_VARIANT(x, y)  cfg.setValue(x, y)
#define REMOVE_CFG_VARIANT(x)   cfg.remove(x)

#define CONFIGPATH QCoreApplication::applicationDirPath() + "/config/"

FileHelper::FileHelper()
{

}

QVariant FileHelper::getSettings(const QString& group, const QString& key)
{
    QSettings cfg(CONFIGPATH + "config.ini", QSettings::IniFormat);

    cfg.beginGroup(group);
    QVariant value = LOAD_CFG_VARIANT(key);
    cfg.endGroup();

    return value;
}

void FileHelper::setSettings(const QString& group, const QString& key, const QVariant& value)
{
    QSettings cfg(CONFIGPATH + "config.ini", QSettings::IniFormat);

    cfg.beginGroup(group);
    SAVE_CFG_VARIANT(key, value);
    cfg.endGroup();
}
