#include "homepage.h"
#include "ui_homepage.h"
#include "listtemplate.h"
#include<QTextEdit>
#include<QDebug>
#include<QPainter>
#include<QButtonGroup>

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->lineEdit_6->setReadOnly(true);
    ui->lineEdit_7->setReadOnly(true);
    ui->lineEdit_8->setReadOnly(true);
    connect(ui->pushButton_modify,&QPushButton::clicked,this,&HomePage::on_pushButton_modify_clicked);
    connect(ui->pushButton_submit,&QPushButton::clicked,this,&HomePage::on_pushButton_submit_clicked);
    ui->Homepge->setStyleSheet(
                                   "QTabWidget::pane{ border:none; }"
                                   "QTabWidget::tab-bar{ alignment:left; }"
                                   "QTabBar::tab{ background:transparent; color:green; min-width:30ex; min-height:10ex; }"
                                   "QTabBar::tab:hover{ background:rgb(255, 255, 255, 100); }"
                                   "QTabBar::tab:selected{ border-color: white; background:white; color:green; }"
                               );
    ui->frame->setStyleSheet(
                "background-color: rgba(255, 255, 255, 128);"
                );
    ui->booking->setFixedSize(100,100);
    ui->prescription_inquiry->setFixedSize(100,100);
    ui->medica_record->setFixedSize(100,100);
    ui->health_evaluate->setFixedSize(100,100);
    prescription_inquiry = new PrescriptionInquiry;
    QVBoxLayout* layout = new QVBoxLayout(ui->scrollAreaWidgetContents); // 创建垂直布局
       layout->setSpacing(10); // 设置布局的间距

      //connect(ui->updatePushbutton, &QPushButton::clicked, this, &HomePage::addCustomWidget); // 点击 "Update" 按钮时添加自定义界面
       connect(ui->prescription_inquiry, &QPushButton::clicked, this, &HomePage::on_prescription_inquiry_clicked);
      setWindowTitle("患者端主页");

      // 创建水平布局管理器
      QHBoxLayout *mainlayout = new QHBoxLayout;

      // 创建 QLabel 控件并设置图片
      QLabel *imageLabel1 = new QLabel;
      QPixmap pixmap1(":/resource111/1.png"); // 设置图片的路径和文件名
      imageLabel1->setPixmap(pixmap1);
      imageLabel1->setScaledContents(true); // 自适应大小

      QLabel *imageLabel2 = new QLabel;
      QPixmap pixmap2(":/resource111/1.png");
      imageLabel2->setPixmap(pixmap2);
      imageLabel2->setScaledContents(true);

      // 将 QLabel 控件添加到布局管理器
      mainlayout->addWidget(imageLabel1);
      mainlayout->addWidget(imageLabel2);

      ui->frame_5->setLayout(mainlayout);
      //实现从处方查询那个界面，跳回到首页
       connect(prescription_inquiry, SIGNAL(preToHome()), this, SLOT(on_PreToHome_Received()) );

       //gerenziliao

       //shezhitouxiang
       QPixmap pixmap(":/resource111/patient_avatar.jpg");
       QPixmap scaledPixmap = pixmap.scaled(QSize(ui->avatar_patient->width(), ui->avatar_patient->height()), Qt::KeepAspectRatio);
       ui->avatar_patient->setPixmap(scaledPixmap);
       ui->avatar_patient->setScaledContents(true);
       ui->avatar_patient->setStyleSheet("QLabel {"
                                         "border-radius: 100px;"  // 设置圆角半径为宽度的一半
                                         "border: 2px solid transparent;"  // 设置边框样式为透明
                                         "}");
       QButtonGroup* group = new QButtonGroup(ui->My);
       group->addButton(ui->pushButton_modify);
       group->addButton(ui->pushButton_submit);
       group->setExclusive(true);

       ui->pushButton_submit->setStyleSheet("QPushButton {"
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
       ui->pushButton_modify->setStyleSheet("QPushButton {"
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

//       建立新的连接
       connect(ui->health_evaluate, &QPushButton::clicked, this, [=]()
       {
           HealthEvaluation *h = new HealthEvaluation;
           h->show();
           this->hide();
       });
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/background.jpg");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);




}


void HomePage::addCustomWidget()
{
    QTextEdit* customWidget = new QTextEdit(ui->scrollAreaWidgetContents); // 创建自定义界面部件
    customWidget->setText("Title");

    customWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 设置大小策略
    ui->scrollAreaWidgetContents->layout()->addWidget(customWidget); // 将自定义界面部件添加到垂直布局中

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
}



void HomePage::on_prescription_inquiry_clicked()
{

    this->hide();
    prescription_inquiry->show();
}

void HomePage::on_PreToHome_Received()
{
    this->show();
    prescription_inquiry->close();

}

void HomePage::on_pushButton_modify_clicked()
{
    ui->lineEdit->setReadOnly(false);
    ui->lineEdit_6->setReadOnly(false);
    ui->lineEdit_7->setReadOnly(false);
    ui->lineEdit_8->setReadOnly(false);
}

void HomePage::on_pushButton_submit_clicked()
{
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->lineEdit_6->setReadOnly(true);
    ui->lineEdit_7->setReadOnly(true);
    ui->lineEdit_8->setReadOnly(true);
}
