#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widgetLevel->setModel(LEVEL);
    ui->widgetPrompt->setModel(PROMPT);
    ui->widgetLevel->setVisible(false);
    ui->widgetPrompt->setVisible(false);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::slot_passwdChanged);
    connect(ui->lnCPasswd, &QLineEdit::textChanged, this, &MainWindow::slot_cpasswdChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_passwdChanged(const QString &value)
{
    ui->widgetLevel->setPassWd(value);
    ui->widgetPrompt->setPassWd(value);

    if(!ui->widgetLevel->checkPasswdStrength())
    {
        ui->widgetPrompt->setPrompt(true);
        return;
    }

    ui->widgetPrompt->setVisible(false);

    if(ui->lnCPasswd->text().isEmpty())
    {
        return;
    }
    if(!ui->widgetPrompt->checkPasswd())
    {
        ui->widgetPrompt->setPrompt(false);
        return;
    }
    ui->widgetPrompt->setVisible(false);
}

void MainWindow::slot_cpasswdChanged(const QString &value)
{
    ui->widgetLevel->setCPasswd(value);
    ui->widgetPrompt->setCPasswd(value);

    if(!ui->widgetLevel->checkPasswdStrength())
    {
        ui->widgetPrompt->setPrompt(true);
        return;
    }

    if(!ui->widgetPrompt->checkPasswd())
    {
        ui->widgetPrompt->setPrompt(false);
        return;
    }
    ui->widgetPrompt->setVisible(false);
}
