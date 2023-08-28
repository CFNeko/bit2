#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrixwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->matrixWidget->initMatrix(4, 4);
    ui->matrixWidget->setMatrixType(MatrixWidget::MatrixType::EDIT_DISABLE);
}

MainWindow::~MainWindow()
{
    delete ui;
}
