#include "changephonenumberpage.h"
#include "ui_changephonenumberpage.h"

ChangePhoneNumberPage::ChangePhoneNumberPage(QWidget *parent, int dno) :
    QWidget(parent),
    ui(new Ui::ChangePhoneNumberPage),
    DoctorID(new int(dno))
{
    ui->setupUi(this);

    RoundedRectButton *submit = new RoundedRectButton;
    QTextEdit *newPhoneNumber = new QTextEdit;
    QString initialText = newPhoneNumber->toPlainText(); // 初始状态的文本

    //    构建布局
    QHBoxLayout *hlayout = new QHBoxLayout;
    {
        hlayout->addStretch(1);

        QVBoxLayout *vlayout = new QVBoxLayout;
        {
            vlayout->addStretch(1);

            vlayout->addWidget(newPhoneNumber);
            vlayout->setStretchFactor(newPhoneNumber, 4);

            QHBoxLayout *button = new QHBoxLayout;
            {
                button->addStretch(2);

                submit->setText("提交");
                button->addWidget(submit);
                button->setStretchFactor(submit, 1);
            }
            vlayout->addLayout(button);
            vlayout->setStretchFactor(button, 1);

            vlayout->addStretch(1);
        }
        hlayout->addLayout(vlayout);
        hlayout->setStretchFactor(vlayout, 5);

        hlayout->addStretch(1);
    }
    this->setLayout(hlayout);

    //    信号连接
    connect(submit, &QPushButton::clicked, this, [=]
    {
        QString currentText = newPhoneNumber->toPlainText();
        if (currentText != initialText) {
            QString changeMessage = "update doctor set doctor.phone = ? where doctor.dno = ?;";
            QSqlQuery query;
            query.prepare(changeMessage);
            query.addBindValue(currentText);
            query.addBindValue(*DoctorID);
            QMessageBox::information(this, "修改成功", "您已成功修改您的电话为："+currentText+"!");
            this->close();
        } else {
            QMessageBox::information(this, "安全退出", "您并未对电话做出修改！");
            this->close();
        }
    });

}
ChangePhoneNumberPage::~ChangePhoneNumberPage()
{
    delete ui;
}
