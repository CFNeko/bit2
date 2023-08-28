#include "login_dialog.h"
#include "ui_login_dialog.h"

#include "file_helper.h"

#include <QtConcurrent/QtConcurrent>
#include <QFuture>

#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->btnCancel, &QPushButton::clicked, [=]{
       reject();
    });

    connect(ui->btnLogin, &QPushButton::clicked, this, [this]{

        QFuture<bool> func = QtConcurrent::run(this, &LoginDialog::onLogin, ui->lnName->text(), ui->lnPasswd->text());
        if(func.result())
        {
            //successfully, @todo something...
            qDebug() << "Login " << func.result();

            if(ui->btnAutoLogin->isChecked() || ui->btnRemember->isChecked())
            {
                FileHelper::instance().setSettings("Login", "user", ui->lnName->text());
                FileHelper::instance().setSettings("Login", "pwd", ui->lnPasswd->text());

                FileHelper::instance().setSettings("Login", "remember", ui->btnRemember->isChecked());
                FileHelper::instance().setSettings("Login", "auto", ui->btnAutoLogin->isChecked());
            }

            accept();
        }
    });

    initPage();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::initPage()
{
    QString r = FileHelper::instance().getSettings("", "").value<QString>();
    ui->btnRemember->setChecked(FileHelper::instance().getSettings("Login", "remember").toBool());
    ui->btnAutoLogin->setChecked(FileHelper::instance().getSettings("Login", "auto").toBool());

    if(ui->btnAutoLogin->isChecked() || ui->btnRemember->isChecked())
    {
        ui->lnName->setText(FileHelper::instance().getSettings("Login", "user").toString());
        ui->lnPasswd->setText(FileHelper::instance().getSettings("Login", "pwd").toString());
    }

    if(ui->btnAutoLogin->isChecked())
    {
        //ui->btnLogin->click();
    }
}

bool LoginDialog::onLogin(const QString &name, const QString &pwd)
{
    //@todo login something...

    qDebug() << name << " " << pwd << "logining...";

    return true;
}


