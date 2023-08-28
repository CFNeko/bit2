#include "registrationpage.h"
#include "ui_registrationpage.h"
#include "userfriendlyitems.h"

#include <QFrame>
#include<QtSql>
#include<QTableWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLabel>
#include<QMessageBox>

RegistrationPage::RegistrationPage(QWidget *parent, int dno) :
    QWidget(parent),
    ui(new Ui::RegistrationPage),
    DoctorID (new int(dno)),
    PatientID (new int())
{
    ui->setupUi(this);

    RoundedRectButton *toRecordItemPage = new RoundedRectButton;
    RoundedRectButton *end = new RoundedRectButton;

    QHBoxLayout *layout = new QHBoxLayout;
    {
        layout->addStretch(1);

        QVBoxLayout *frameLayout = new QVBoxLayout;
        {
            //    查询医生名字
            QSqlQuery query_;
            QString qs_ = "select doctor.name "
                          "from doctor "
                          "where dno = ";
            query_.prepare(qs_);
            query_.bindValue(0, (*PatientID));
            //    医生预约欢迎栏
            QString s = "";
            s += query_.value(2).toString();
            s += "医生，您好！这是您今日预约，愿您妙手荡尽魑魅!";
            QLabel *info = new QLabel;
            info->setText(s);

            frameLayout->addWidget(info);
            frameLayout->setStretchFactor(info, 1);

            //    查询医生所有的预约
            QSqlQuery query;
            QString qs = "select patient.pno, patient.name, registration.dueTime, patient.phone "
                         "from registration left join patient "
                         "where registration.dno = ? and registration.complete = 0;";
            query.prepare(qs);
            query.bindValue(0, (*PatientID));
            //     添加一些内容到表格
            QStringList headerLabels;
            headerLabels << "患者编号"<< "预约患者" << "预约时间" << "联系电话";
            registrationTable->setHorizontalHeaderLabels(headerLabels);
            if (query.exec()) {
                int row = 0;
                while (query.next()) {
                    QString duetimeStr = query.value(4).toString();
                    QDateTime dueDateTime = QDateTime::fromString(duetimeStr, "yyyy-MM-dd hh:mm:ss");
                    QDateTime currentDateTime = QDateTime::currentDateTime();
                    if(dueDateTime.date() == currentDateTime.date()){
                        registrationTable->insertRow(row);
                        for(int i = 0; i < 4; i++){
                            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
                            registrationTable->setItem(row, i, item);
                        }
                        ++row;
                        qDebug() << "Load Successfully! " << query.lastError();
                    }
                }
            } else {
                qDebug() << "Error querying data: " << query.lastError();
            }
            frameLayout->addWidget(registrationTable);
            frameLayout->setStretchFactor(registrationTable, 4);

            //        订单页面操作按钮
            QHBoxLayout *buttonsFrame = new QHBoxLayout;
            {

                toRecordItemPage->setText("编辑病历");
                buttonsFrame->addWidget(toRecordItemPage);
                buttonsFrame->setStretchFactor(toRecordItemPage, 1);

                buttonsFrame->addStretch(3);


                end->setText("结束诊治");
                buttonsFrame->addWidget(end);
                buttonsFrame->setStretchFactor(end, 1);
            }
        }
        layout->addLayout(frameLayout);
        layout->setStretchFactor(frameLayout, 2);

        layout->addStretch(1);
    }

    this->setLayout(layout);

    //    信号连接
    connect(toRecordItemPage, &QPushButton::clicked, this, [this]
    {

//        QList<QTableWidgetItem *> selectedItems = registrationTable->selectedItems();
//        QString rno = "";
//        rno.clear();
//        if (!selectedItems.isEmpty()) {
//            QTableWidgetItem *item = selectedItems.last();
//            int row = item->row();
//            rno = registrationTable->item(row, 0)->text();
//        } else{
//            QMessageBox::warning(this, "操作失败", "请先选中患者所在列！");
//        }
//               RecordItemPage *recordItemPage = new RecordItemPage;

    });

    connect(end, &QPushButton::clicked, this, [this]
    {
        //    根据选中行确定患者
        QList<QTableWidgetItem *> selectedItems = registrationTable->selectedItems();
        QString rno = "";
        rno.clear();
        if (!selectedItems.isEmpty()) {
            QTableWidgetItem *item = selectedItems.last();
            int row = item->row();
            rno = registrationTable->item(row, 0)->text();
        } else{
            QMessageBox::warning(this, "操作失败", "请先选中患者所在列！");
        }

        //    执行完成诊治对后台表的修改
        QSqlQuery complete;
        QString str = QString("UPDATE registration SET complete = ? WHERE rno = ?");
        complete.prepare(str);
        complete.addBindValue(1);
        complete.addBindValue(rno);
        if (complete.exec()) {
//            清除旧表
            QMessageBox::information(this, "完成诊断", "您已完成其诊治！");
            registrationTable->clearContents();

//            开新表
            QSqlQuery query;
            QString qs = "select patient.pno, patient.name, registration.dueTime, patient.phone "
                         "from registration left join patient "
                         "where registration.dno = ? and registration.complete = 0;";
            query.prepare(qs);
            query.bindValue(0, (*PatientID));
            //    建立表来展示预约信息
            registrationTable = new QTableWidget();
            //     添加一些内容到表格
            QStringList headerLabels;
            headerLabels << "患者编号"<< "预约患者" << "预约时间" << "联系电话";
            registrationTable->setHorizontalHeaderLabels(headerLabels);
            if (query.exec()) {
                int row = 0;
                while (query.next()) {
                    QString duetimeStr = query.value(4).toString();
                    QDateTime dueDateTime = QDateTime::fromString(duetimeStr, "yyyy-MM-dd hh:mm:ss");
                    QDateTime currentDateTime = QDateTime::currentDateTime();
                    if(dueDateTime.date() == currentDateTime.date()){
                        registrationTable->insertRow(row);
                        for(int i = 0; i < 4; i++){
                            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
                            registrationTable->setItem(row, i, item);
                        }
                        ++row;
                        qDebug() << "Load Successfully! " << query.lastError();
                    }
                }
            } else {
                qDebug() << "Error querying data: " << query.lastError();
            }

        }else {
            qDebug() << "Error querying data: " << complete.lastError();
        }
    });

}
