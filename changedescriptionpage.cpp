#include "changedescriptionpage.h"
#include "ui_changedescriptionpage.h"

ChangeDescriptionPage::ChangeDescriptionPage(QWidget *parent, int dno) :
    QWidget(parent),
    ui(new Ui::ChangeDescriptionPage),
    DoctorID(new int(dno))
{
    ui->setupUi(this);

    RoundedRectButton *submit = new RoundedRectButton;
    QTextEdit *newDescription = new QTextEdit;
    QString initialText = newDescription->toPlainText();
    //        读取数据库中的描述
    QString qs = "select * from doctor where doctor.dno = ";
    qs += QString(*DoctorID);
    qs += ";";
    QSqlQuery query;
    if (query.exec(qs)) {
        qDebug() << "Load Successfully! " << query.lastError();
    } else {
        qDebug() << "Error querying data: " << query.lastError();
        this->close();
    }
    QString oldDescription = query.value(6).toString();
    newDescription->setText(oldDescription);

    //    构建布局
    QHBoxLayout *hlayout = new QHBoxLayout;
    {
        hlayout->addStretch(1);

        QVBoxLayout *vlayout = new QVBoxLayout;
        {
            vlayout->addStretch(1);

            vlayout->addWidget(newDescription);
            vlayout->setStretchFactor(newDescription, 4);

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
        QString currentText = newDescription->toPlainText();
        if (currentText != initialText) {
            QString changeMessage = "update doctor set doctor.desc = ? where doctor.dno = ?;";
            QSqlQuery query;
            query.prepare(changeMessage);
            query.addBindValue(currentText);
            query.addBindValue(*DoctorID);
            QMessageBox::information(this, "修改成功", "您已成功修改您的描述！");
            this->close();
        } else {
            QMessageBox::information(this, "安全退出", "您并未对您的描述做出修改！");
            this->close();
        }
    });

}

ChangeDescriptionPage::~ChangeDescriptionPage()
{
    delete ui;
}
