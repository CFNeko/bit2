#include "changepasswordpage.h"
#include "ui_changepasswordpage.h"

ChangePasswordPage::ChangePasswordPage(QWidget *parent, int dno) :
    QWidget(parent),
    ui(new Ui::ChangePasswordPage),
    DoctorID(new int(dno))
{
    ui->setupUi(this);

    RoundedRectButton *submit = new RoundedRectButton;
    RoundedRectButton *cancel = new RoundedRectButton;
    QLineEdit *oldPassword = new QLineEdit;
    QLineEdit *newPassword = new QLineEdit;
    QLineEdit *confirmPassword = new QLineEdit;

    QHBoxLayout *hlayout = new QHBoxLayout;
    {
        hlayout->addStretch(1);

        QVBoxLayout *vlayout = new QVBoxLayout;
        {
            vlayout->addStretch(1);

            QHBoxLayout *old = new QHBoxLayout;
            {
                QLabel *o = new QLabel;
                o->setText("原始密码：");
                old->addWidget(o);
                old->setStretchFactor(o, 1);

                old->addWidget(oldPassword);
                old->setStretchFactor(oldPassword, 5);
            }
            vlayout->addLayout(old);
            vlayout->setStretchFactor(old, 2);


            QHBoxLayout *newp = new QHBoxLayout;
            {
                QLabel *n = new QLabel;
                n->setText("新的密码：");
                newp->addWidget(n);
                newp->setStretchFactor(n, 1);

                newp->addWidget(oldPassword);
                newp->setStretchFactor(oldPassword, 5);
            }
            vlayout->addLayout(newp);
            vlayout->setStretchFactor(newp, 2);

            QHBoxLayout *con = new QHBoxLayout;
            {
                QLabel *c = new QLabel;
                c->setText("原密码：");
                con->addWidget(c);
                con->setStretchFactor(c, 1);

                con->addWidget(oldPassword);
                con->setStretchFactor(oldPassword, 5);
            }
            vlayout->addLayout(con);
            vlayout->setStretchFactor(con, 2);

            QHBoxLayout *button = new QHBoxLayout;
            {
                submit->setText("保存");
                button->addWidget(submit);
                button->setStretchFactor(submit, 1);

                cancel->setText("取消");
                button->addWidget(cancel);
                button->setStretchFactor(cancel, 1);
            }
            vlayout->addLayout(button);
            vlayout->setStretchFactor(button, 2);

            vlayout->addStretch(1);
        }
        hlayout->addLayout(vlayout);
        hlayout->setStretchFactor(vlayout, 2);

        hlayout->addStretch(1);
    }
    this->setLayout(hlayout);

    //    信号连接
    connect(cancel, &QPushButton::clicked, this, [=]
    {
        this->close();
    });
    connect(submit, &QPushButton::clicked, this, [=]
    {
        //        读取数据库中密码
        QString qs = "select * from doctor where doctor.dno = ";
        qs += QString(*DoctorID);
        qs += ";";
        QSqlQuery query;
        if (query.exec(qs)) {
            qDebug() << "Load Successfully! " << query.lastError();

        } else {
            qDebug() << "Error querying data: " << query.lastError();
        }
        QString *password = new QString(query.value(1).toString());
        //        这里如果有加密需求，需要检查加密后的秘文
        if (password == oldPassword->text()) {
            if(newPassword->text() != confirmPassword->text()){
                QMessageBox::warning(this, "操作失败", "新密码未被确认！");
            } else {
                QString changeMessage = "update doctor set doctor.password = ? where doctor.dno = ?;";
                query.prepare(changeMessage);
                query.addBindValue(newPassword->text());
                query.addBindValue(*DoctorID);
                if (query.exec()) {
                    qDebug() << "Load Successfully! " << query.lastError();
                    QMessageBox::information(this, "操作成功", "您的密码已修改，请牢记新密码："+newPassword->text() + "!");
                    this->close();
                } else {
                    qDebug() << "Error querying data: " << query.lastError();
                }
            }
        } else {
            QMessageBox::warning(this, "操作失败", "原始密码不正确，您的身份未确认！");
        }
    });

}

ChangePasswordPage::~ChangePasswordPage()
{
    delete ui;
}
