#include "ipconfig.h"
#include "ui_ipconfig.h"

IpConfigWidget::IpConfigWidget(QWidget *parent) : QWidget(parent), ui(new Ui::IpConfigWidget)
{
    ui->setupUi(this);

    ui->spinBox->clear();
    QRegExp rx("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    QRegExpValidator* ipValidator = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(ipValidator);

}

IpConfigWidget::~IpConfigWidget()
{
    delete ui;
}

QString IpConfigWidget::ip() const
{
    QString ip = ui->lineEdit->text();
    return ip;
}

void IpConfigWidget::setIp(const QString& ip)
{
    ui->lineEdit->setText(ip);
}

int IpConfigWidget::port() const
{
    return ui->spinBox->value();
}

void IpConfigWidget::setPort(const int &port)
{
    ui->spinBox->setValue(port);
}
