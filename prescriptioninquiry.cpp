#include "prescriptioninquiry.h"
#include "ui_prescriptioninquiry.h"
#include<QPainter>
#include<QPushButton>

PrescriptionInquiry::PrescriptionInquiry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescriptionInquiry)
{
    ui->setupUi(this);
    this->setFixedSize(900,600);

    //4.设置窗口标题
    this->setWindowTitle("处方查询系统");

    connect(ui->exitPushbutton,&QPushButton::clicked,this,&PrescriptionInquiry::on_pushButton_clicked);

}

void PrescriptionInquiry::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/background.jpg");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);

}


PrescriptionInquiry::~PrescriptionInquiry()
{
    delete ui;
}


void PrescriptionInquiry::on_pushButton_clicked()
{
    emit  preToHome();
}
