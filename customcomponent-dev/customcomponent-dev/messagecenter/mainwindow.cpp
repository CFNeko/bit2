#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagecenter.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int nIndex = 0; nIndex <= 5; ++nIndex)
    {
        ErrorInfo error;
        error.code = SERVICE_DISCONNECT;
        error.info = "service disconnected.";
        error.solution = "please check the net work and service.";
        error.deleted = true;

        MessageCenter::Instance()->pushError("ServiceDisconnected", error);
    }

    connect(MessageCenter::Instance(), &MessageCenter::signal_errorCount, this, &MainWindow::slot_msgCount);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MessageCenter::Instance()->show();
}

void MainWindow::slot_msgCount(int count)
{
    ui->pushButton->setText(QString::number(count));
}
