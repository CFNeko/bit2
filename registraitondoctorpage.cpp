#include "registraitondoctorpage.h"
#include "ui_registraitondoctorpage.h"

RegistraitonDoctorPage ::RegistraitonDoctorPage(QWidget *parent, bool judge) :
    QWidget(parent),
    ui(new Ui::RegistraitonDoctorPage),
    isHistory(judge)
{
    ui->setupUi(this);
    this->setFixedSize(1000, 800);

    QVBoxLayout *pagelayout = new QVBoxLayout;
    {
        //        欢迎栏目
        QHBoxLayout *toplayout = new QHBoxLayout;
        {
            toplayout->addStretch(1);

            QLabel *toplabel = new QLabel;
            // 创建一个字体
            QFont customFont;
            customFont.setFamily("Arial");    // 设置字体家族
            customFont.setPointSize(36);      // 设置字体大小

            // 设置标签的字体
            toplabel->setFont(customFont);
            toplabel->setAlignment(Qt::AlignCenter);

            //            api函数
            if(!isHistory){
                toplabel->setText("~~医生，这是您今日的挂号预约！\n愿您妙手荡尽魑魅");
            }else{
                toplabel->setText("~~医生，这是您的挂号预约记录！");
            }
            toplayout->addWidget(toplabel);
            toplayout->setStretchFactor(toplabel, 1);

            toplayout->addStretch(1);
        }
        pagelayout->addLayout(toplayout);
        pagelayout->setStretchFactor(toplayout, 3);

        //        摘要显示部分
        QFrame *mainFrame = new QFrame;
        QScrollArea *mainArea = new QScrollArea;
        QHBoxLayout *mainlayout = new QHBoxLayout;
        {
            //            测试用，只有9个
            for(int i = 0; i < 9; i++){
                RegistrationButton *content = new RegistrationButton;
                QVBoxLayout *columnlayout = new QVBoxLayout;
                {
                    columnlayout->addStretch(1);

                    QVBoxLayout *contentlayout = new QVBoxLayout;
                    {
                        contentlayout->addStretch(2);

                        QHBoxLayout *namelayout = new QHBoxLayout;
                        {
                            QLabel *namelabel = new QLabel;
                            QLabel *nameshow = new QLabel;
                            // 创建一个字体
                            QFont contentFont;
                            contentFont.setFamily("Arial");    // 设置字体家族
                            contentFont.setPointSize(15);      // 设置字体大小

                            // 设置标签的字体
                            nameshow->setFont(contentFont);
                            nameshow->setAlignment(Qt::AlignCenter);
                            namelabel->setFont(contentFont);
                            namelabel->setAlignment(Qt::AlignCenter);
                            namelabel->setText("患者姓名：");
                            nameshow->setText("蔡余申");

                            namelayout->addWidget(namelabel);
                            namelayout->addWidget(nameshow);
                        }

                        QHBoxLayout *timelayout = new QHBoxLayout;
                        {
                            QLabel *timelabel = new QLabel;
                            QLabel *timeshow = new QLabel;

                            // 创建一个字体
                            QFont contentFont;
                            contentFont.setFamily("Arial");    // 设置字体家族
                            contentFont.setPointSize(13);      // 设置字体大小

                            timeshow->setFont(contentFont);
                            timeshow->setAlignment(Qt::AlignCenter);
                            timelabel->setFont(contentFont);
                            timelabel->setAlignment(Qt::AlignCenter);

                            timelabel->setText("预约时间：");
                            timeshow->setText("2023.8.27");

                            timelayout->addWidget(timelabel);
                            timelayout->addWidget(timeshow);
                        }

                        contentlayout->addLayout(namelayout);
                        contentlayout->addStretch(1);
                        contentlayout->addLayout(timelayout);

                        contentlayout->addStretch(2);
                    }
                    content->setLayout(contentlayout);

                    //                    这里需要补充检查对应病历
                    connect(content, &QPushButton::clicked, this, [=]
                    {
                        RecordItemTable *r = new RecordItemTable;
                        r->show();
                        this->hide();
                        connect(r, &RecordItemTable::riClosed, this, &QWidget::show);
                    });

                    columnlayout->addWidget(content);
                    content->setFixedSize(200, 300);
                    columnlayout->setStretchFactor(content, 5);

                    columnlayout->addStretch(1);
                }
                mainlayout->addLayout(columnlayout);

            }

            mainFrame->setLayout(mainlayout);
            mainArea->setWidget(mainFrame);
        }
        pagelayout->addWidget(mainArea);
        pagelayout->setStretchFactor(mainArea, 5);

        if(!isHistory){
            QHBoxLayout *buttonlayout = new QHBoxLayout;
            {
                buttonlayout->addStretch(4);

                QPushButton *finish = new QPushButton;
                finish->setText("结束诊治");
                buttonlayout->addWidget(finish);
                buttonlayout->setStretchFactor(finish, 1);
            }

            pagelayout->addLayout(buttonlayout);
            pagelayout->setStretchFactor(buttonlayout, 1);
        }

        pagelayout->addStretch(1);
    }

    //    connect(this, &QWidget::close, this, [=]
    //    {
    //        DoctorPage *d = new DoctorPage;
    //        d->show();
    //    });
    this->setLayout(pagelayout);

}

RegistraitonDoctorPage::~RegistraitonDoctorPage()
{
    delete ui;
}

void RegistraitonDoctorPage::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/background.jpg");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);
}
