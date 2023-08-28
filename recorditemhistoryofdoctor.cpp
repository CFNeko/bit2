#include "recorditemhistoryofdoctor.h"
#include "ui_recorditemhistoryofdoctor.h"
#include "recorditemtable.h"

RecordItemHistoryofDoctor::RecordItemHistoryofDoctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordItemHistoryofDoctor)
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
            //            api函数
            toplabel->setText("~~医生的历史病历");
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
                            namelabel->setText("患者姓名：");
                            nameshow->setText("蔡余申");

                            namelayout->addWidget(namelabel);
                            namelayout->addWidget(nameshow);
                        }

                        QHBoxLayout *timelayout = new QHBoxLayout;
                        {
                            QLabel *timelabel = new QLabel;
                            QLabel *timeshow = new QLabel;
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

//        QHBoxLayout *buttonlayout = new QHBoxLayout;
//        {
//            buttonlayout->addStretch(3);

//            QPushButton *query = new QPushButton;
//            query->setText("查看病历");

//            buttonlayout->addWidget(query);
//            buttonlayout->setStretchFactor(query, 1);

//        }
//        pagelayout->addLayout(buttonlayout);

        pagelayout->addStretch(1);
    }

//    connect(this, &QWidget::close, this, [=]
//    {
//        DoctorPage *d = new DoctorPage;
//        d->show();
//    });
    this->setLayout(pagelayout);


}

RecordItemHistoryofDoctor::~RecordItemHistoryofDoctor()
{
    delete ui;
}

void RecordItemHistoryofDoctor::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/background.jpg");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);
}
