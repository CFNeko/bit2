#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mask_widget.h"
#include "dialog.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MaskWidget::instance()->setMainWidget(this);

    QStringList listName;

    listName << "Dialog";

    MaskWidget::instance()->setNames(listName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Dialog dlg;
    if(QDialog::Accepted == dlg.exec())
    {

    }
}
