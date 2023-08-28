#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "table_defines.h"
#include <QVariantList>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list;

    list << "name" << "class" << "score" << "address" << "operate";

    ui->wdgData->initTableHeader(list);

    QList<int> width;
    width << 100 << 100 << 100 << 200 << 200;

    ui->wdgData->initTableColumnWidth(width);

    QVariantList row, t;

    row << "zhangsan" << "class three" << 99 << "nanhu street";
    t << "wangwu" << "class three" << 98 << "nanhu street";

    QList<QVariantList> data;
    for(int index = 0; index < 50; ++index)
    {
        data.append(row);
        data.append(t);
    }

    ui->wdgData->setTableData(data);

    QVariantList op;
    op << UserOperate::OPERATE_EDIT << UserOperate::OPERATE_DELETE;
    ui->wdgData->setTableColumnOperates(5, op);

    connect(ui->wdgData, &TableWidget::signal_operate, this, [this](const QVariant& op, const QVariant& data)
    {
        qDebug() << op << data;

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
