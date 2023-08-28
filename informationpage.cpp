#include "informationpage.h"
#include "ui_informationpage.h"

InformationPage::InformationPage(QWidget *parent, int dno) :
    QWidget(parent),
    ui(new Ui::InformationPage),
    DoctorID(new int(dno))
{
    ui->setupUi(this);

//    读取医生信息
    QString qs = "select * from doctor where doctor.dno = ";
    qs += QString(*DoctorID);
    qs += ";";
    QSqlQuery query;
    if (query.exec(qs)) {
        qDebug() << "Load Successfully! " << query.lastError();

    } else {
        qDebug() << "Error querying data: " << query.lastError();
    }

//    建立布局
    RoundedRectButton *ChangePassword = new RoundedRectButton;
    RoundedRectButton *ChangePhoneNumber = new RoundedRectButton;
    RoundedRectButton *ChangeDescription = new RoundedRectButton;


    QHBoxLayout *hlayout = new QHBoxLayout;
    {
        hlayout->addStretch(1);

        QVBoxLayout *vlayout = new QVBoxLayout;
        {
            vlayout->addStretch(2);



            ChangePassword->setText("修改密码");
            vlayout->addWidget(ChangePassword);
            vlayout->setStretchFactor(ChangePassword, 1);

            ChangePhoneNumber->setText("修改手机号");
            vlayout->addWidget(ChangePhoneNumber);
            vlayout->setStretchFactor(ChangePhoneNumber, 1);

            ChangeDescription->setText("修改介绍");
            vlayout->addWidget(ChangeDescription);
            vlayout->setStretchFactor(ChangeDescription, 1);

            vlayout->addStretch(1);
        }
        hlayout->addLayout(vlayout);
        hlayout->setStretchFactor(vlayout, 1);

        hlayout->addStretch(1);
    }

    this->setLayout(hlayout);

//    信号函数
    connect(ChangePassword, &QPushButton::clicked, this, [=]
    {
        ChangePasswordPage *p = new ChangePasswordPage(nullptr, *DoctorID);
        p->show();
    });

    connect(ChangePhoneNumber, &QPushButton::clicked, this, [=]
    {
        ChangePhoneNumberPage *n = new ChangePhoneNumberPage(nullptr, *DoctorID);
        n->show();
    });

    connect(ChangeDescription, &QPushButton::clicked, this, [=]
    {
        ChangeDescriptionPage *d = new ChangeDescriptionPage(nullptr, *DoctorID);
        d->show();
    });
}

InformationPage::~InformationPage()
{
    delete ui;
}
