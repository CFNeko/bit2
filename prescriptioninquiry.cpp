#include "prescriptioninquiry.h"
#include "ui_prescriptioninquiry.h"
#include<QPainter>
#include<QPushButton>
#include<QWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QScrollArea>
#include<QLabel>

PrescriptionInquiry::PrescriptionInquiry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescriptionInquiry)
{
    ui->setupUi(this);
    this->setFixedSize(900,600);

    //4.设置窗口标题
    this->setWindowTitle("处方查询系统");

    connect(ui->exitPushbutton,&QPushButton::clicked,this,&PrescriptionInquiry::on_pushButton_clicked);

    //点击查询历史处方
    // 创建滚动区域的内容部件

        ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);

        QHBoxLayout* lineLayout = new QHBoxLayout(ui->scrollAreaWidgetContents);


            // 创建添加按钮的槽函数
            connect(ui->inquirepushbutton, &QPushButton::clicked,[=]() {
                // 创建垂直布局并设置给滚动区域的内容部件
                QVBoxLayout* verticalLayout = new QVBoxLayout();
                verticalLayout->setContentsMargins(10, 10, 10, 10); // 设置外边距为10像素

                QPushButton* button = new QPushButton();
                button->setStyleSheet("QPushButton { border-radius: 80px; }");

                 QLabel* title =new QLabel("门诊病例");
                QLabel* doc_name =new QLabel("医生姓名：jenny");
                QLabel* illness =new QLabel("病情诊断：bad cold");
                QLabel* treatment_date =new QLabel("就诊日期：2023/8/27");
                title->setAlignment(Qt::AlignCenter);
                // 设置字体样式
                title->setFont(QFont("楷体", 30,QFont::Bold));
                // 设置背景色透明
                title->setStyleSheet("QLabel { background-color: transparent; }");
                doc_name->setAlignment(Qt::AlignCenter);
                // 设置字体样式
                doc_name->setFont(QFont("楷体", 15));
                // 设置背景色透明
                doc_name->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 128); }");
                illness->setAlignment(Qt::AlignCenter);
                // 设置字体样式
                illness->setFont(QFont("楷体", 15));
                // 设置背景色透明
                illness->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 128); }");
                treatment_date->setAlignment(Qt::AlignCenter);
                // 设置字体样式
                treatment_date->setFont(QFont("楷体", 15));
                // 设置背景色透明
                treatment_date->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 128); }");
                QVBoxLayout* labels_layout = new QVBoxLayout();
                labels_layout->addWidget(title);
                labels_layout->addWidget(doc_name);
                labels_layout->addWidget(illness);
                labels_layout->addWidget(treatment_date);
                labels_layout->setStretchFactor(title,5);
                labels_layout->setStretchFactor(doc_name,2);
                labels_layout->setStretchFactor(illness,2);
                labels_layout->setStretchFactor(treatment_date,2);

                button->setLayout(labels_layout);

                button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                button->setFixedSize(233,327); // 设置按钮的固定大小
                button->setStyleSheet("QPushButton { background-image: url(:/resource111/background1.jpg); background-repeat: no-repeat; background-position: center; background-size: contain; }");
                verticalLayout->addWidget(button);
                lineLayout->addLayout(verticalLayout);
            });

         ui->scrollAreaWidgetContents->setLayout(lineLayout);

         QPixmap pixmap(":/resource111/patient_avatar.jpg");
         QPixmap scaledPixmap = pixmap.scaled(QSize(ui->avatar_patient->width(), ui->avatar_patient->height()), Qt::KeepAspectRatio);
         ui->avatar_patient->setPixmap(scaledPixmap);
         ui->avatar_patient->setScaledContents(true);
         ui->avatar_patient->setStyleSheet("QLabel {"
                                           "border-radius: 100px;"  // 设置圆角半径为宽度的一半
                                           "border: 2px solid transparent;"  // 设置边框样式为透明
                                           "}");
         // 设置边框样式
         ui->scrollArea->setStyleSheet("QScrollArea { border: 2px solid blue; }");

         // 设置背景颜色
         ui->scrollArea->setStyleSheet("QScrollArea { background-color: white; }");

         ui->inquirepushbutton->setStyleSheet("QPushButton {"
                                              "background-color: white;"  // 设置默认背景色为白色
                                              "border: none;"  // 移除边框
                                              "border-radius: 5px;"  // 设置圆角
                                              "padding: 5px;"  // 设置内边距
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: #eaeaea;"  // 设置悬停时的背景色为浅灰色
                                              "}"
                                              "QPushButton:pressed {"
                                              "background-color: #c0c0c0;"  // 设置按下时的背景色为稍深灰色
                                              "border-style: inset;"  // 添加下沉效果
                                              "}"
                                              "QPushButton:released {"
                                              "border-style: none;"  // 恢复无边框样式
                                              "}");
}

void PrescriptionInquiry::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/background1.jpg");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);

}


PrescriptionInquiry::~PrescriptionInquiry()
{
    delete ui;
}


void PrescriptionInquiry::on_pushButton_clicked()
{
   emit preToHome();
}

