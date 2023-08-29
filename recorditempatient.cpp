#include "recorditempatient.h"
#include "ui_recorditempatient.h"

RecordItemPatient::RecordItemPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordItemPatient)
{
    ui->setupUi(this);

    connect(this, &QWidget::destroyed, this, &RecordItemPatient::rpClosed);
}

RecordItemPatient::~RecordItemPatient()
{
    delete ui;
}
