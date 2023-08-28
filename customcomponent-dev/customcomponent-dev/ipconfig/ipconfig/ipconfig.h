#ifndef IPCONFIG_H
#define IPCONFIG_H

#include <QWidget>

namespace Ui {
class IpConfigWidget;
}

class IpConfigWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString ip READ ip WRITE setIp DESIGNABLE true)
    Q_PROPERTY(int port READ port WRITE setPort DESIGNABLE true)

public:
    explicit IpConfigWidget(QWidget *parent = 0);
    ~IpConfigWidget();

    QString ip() const;
    void setIp(const QString& ip);
    int port() const;
    void setPort(const int& port);

private:
    Ui::IpConfigWidget *ui;
};

#endif // IPCONFIG_H
