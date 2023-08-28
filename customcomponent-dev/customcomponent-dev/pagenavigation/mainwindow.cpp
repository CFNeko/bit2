#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setTotal(386);

    connect(ui->widget, &PageNavigationWidget::signal_page, this, [this](int index)
    {
        qDebug() << index;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
