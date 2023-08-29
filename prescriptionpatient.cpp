#include "prescriptionpatient.h"
#include "ui_prescriptionpatient.h"

PrescriptionPatient::PrescriptionPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescriptionPatient)
{
    ui->setupUi(this);
    connect(this, &QWidget::destroyed, this, &PrescriptionPatient::pptClosed);
}

PrescriptionPatient::~PrescriptionPatient()
{
    delete ui;
}
