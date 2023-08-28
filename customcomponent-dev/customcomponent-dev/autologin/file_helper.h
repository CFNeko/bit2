#ifndef FILEHELPER_H
#define FILEHELPER_H

#include<QObject>
class FileHelper
{
public:

    static FileHelper& instance()
    {
        static FileHelper instance;
        return instance;
    }

    QVariant getSettings(const QString& group, const QString& key);
    void setSettings(const QString& group, const QString& key, const QVariant& value);

private:

    FileHelper();
};

#endif // FILEHELPER_H
