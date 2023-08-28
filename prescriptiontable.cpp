#include "prescriptiontable.h"
#include "ui_prescriptiontable.h"

PrescriptionTable::PrescriptionTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescriptionTable)
{
    ui->setupUi(this);

    connect(ui->submit, &QPushButton::clicked, this, [=]
    {
        if(IsLegal()){
            QMessageBox::information(this, "处方保存成功", "您编辑的处方保存成功！");
            this->close();
        }else {
            QMessageBox::information(this, "处方保存失败", "请检查您的处方！");
        }
    });
}

PrescriptionTable::~PrescriptionTable()
{
    delete ui;
}

bool PrescriptionTable::IsLegal()
{

}
