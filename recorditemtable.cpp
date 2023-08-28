#include "recorditemtable.h"
#include "ui_recorditemtable.h"

RecordItemTable::RecordItemTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordItemTable)
{
    ui->setupUi(this);
    connect(ui->toPrescription, &QPushButton::clicked, this, [=]
    {
        PrescriptionTable *p = new PrescriptionTable;
        p->show();
    });
}

RecordItemTable::~RecordItemTable()
{
    delete ui;
}
