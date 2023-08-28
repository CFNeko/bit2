include "prescriptionpage.h"
#include "ui_prescriptionpage.h"

PrescriptionPage::PrescriptionPage(QWidget *parent, int dno, int pno, int rgno) :
    QWidget(parent),
    ui(new Ui::PrescriptionPage),
    DoctorID(new int(dno)),
    PatientID(new int(pno)),
    RegistrationID(new int(rgno)),
    mno(new int())
{
    ui->setupUi(this);

    RoundedRectButton *submit = new RoundedRectButton;
    QLineEdit *mname = new QLineEdit;
    QLineEdit *amount = new QLineEdit;
    QTextEdit *advice = new QTextEdit;
    submit->setText("保存并退出");

    QHBoxLayout *hlayout = new QHBoxLayout;
    {
        hlayout->addStretch(1);

        QVBoxLayout *vlayout = new QVBoxLayout;
        {

            //            药品名称
            QHBoxLayout *namelayout = new QHBoxLayout;
            {
                QLabel *namelabel = new QLabel;
                namelabel->setText("药品名：");
                namelayout->addWidget(namelabel);
                namelayout->setStretchFactor(namelabel, 1);
                namelayout->addWidget(mname);
                namelayout->setStretchFactor(mname, 4);
            }
            vlayout->addLayout(namelayout);
            vlayout->setStretchFactor(namelayout, 2);

            vlayout->addStretch(1);

            //            图像上传
            QHBoxLayout *amountlayout = new QHBoxLayout;
            {
                QLabel *amountlabel = new QLabel;
                amountlabel->setText("剂量：");
                namelayout->addWidget(amountlabel);
                namelayout->setStretchFactor(amountlabel, 1);
                namelayout->addWidget(amount);
                namelayout->setStretchFactor(amount, 4);
            }
            vlayout->addLayout(amountlayout);
            vlayout->setStretchFactor(amountlayout, 2);

            QLabel *advicelabel = new QLabel;
            advicelabel->setText("医嘱：");
            vlayout->addWidget(advicelabel);
            vlayout->setStretchFactor(advicelabel, 1);



            advice->setPlainText("多喝热水！");
            vlayout->addWidget(advice);
            vlayout->setStretchFactor(advice, 2);

            QHBoxLayout *buttonlayout = new QHBoxLayout;
            {
                buttonlayout->addStretch(2);

                buttonlayout->addWidget(submit);
                buttonlayout->setStretchFactor(submit, 1);
            }
            vlayout->addLayout(buttonlayout);
            vlayout->setStretchFactor(buttonlayout, 1);

            vlayout->addStretch(1);

        }
        hlayout->addLayout(vlayout);
        hlayout->setStretchFactor(vlayout, 1);

        hlayout->addStretch(1);
    }
    this->setLayout(hlayout);

    connect(submit, &QPushButton::clicked, this, [=]
    {
        if(amount->text().isEmpty() || mname->text().isEmpty() || advice->toPlainText().isEmpty()){
            QMessageBox::information(this, "操作失败", "您并未给出处方！");
        }
        else{
            QSqlQuery *updateQuery = new QSqlQuery;
            QString updateMessage = "update prescription insert prescription(rno, mno, num, advice) values (?, ?, ?, ?)";
            updateQuery->prepare(updateMessage);
            updateQuery->addBindValue(*RegistrationID);
            updateQuery->addBindValue(*mno);
            updateQuery->addBindValue(amount->text().toFloat());
            updateQuery->addBindValue(advice->toPlainText());
            QMessageBox::information(this, "操作成功", "您给出新的处方！");
            this->close();
        }
    });

}

PrescriptionPage::~PrescriptionPage()
{
    delete ui;
}
