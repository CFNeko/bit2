#include "qmywidget.h"

QMyWidget::QMyWidget(QString str_name_, int tempid_, QWidget *parent)
    : QWidget(parent),str_name(str_name_),tempid(tempid_)
{
    //设置背景图片
    this->resize(690,500);
    //设置医生头像
    label_pic = new QLabel(this);
    label_pic->move(45,15);
    label_pic->setFixedSize(170,200);
    label_pic->setScaledContents(true);
    label_pic->setPixmap(QPixmap(":/myresource/doctor_pic.jpg"));
    label_pic->show();
    //设置医生简介信息
    label_info = new QMylabel(this);
    label_info->setFixedSize(400, 215);
    //设置日历
    QCalendarWidget *calendar = new QCalendarWidget(this);
    calendar->move(25,230);
    calendar->setFixedSize(460,260);
    //设置可选日期的最值
    QDate currentdate = QDate::currentDate();
    calendar->setMinimumDate(currentdate);
    calendar->setMaximumDate(QDate::fromString( currentdate.addDays(+7).toString("yyyy-MM-dd"), "yyyy-MM-dd" ));
    //设置禁用日期
    QTextCharFormat disabledFormat;
    disabledFormat.setForeground(Qt::gray); // 设置文本颜色为灰色
    disabledFormat.setFontStrikeOut(true);  //添加下划线
    calendar->setDateTextFormat(currentdate/*被禁用日期*/, disabledFormat);
    //设置预约/问诊按钮
    QMyButton *submit = new QMyButton(this);
    submit->move(510,270);
    submit->setFixedSize(130,60);
    submit->setText("预约");
    QMyButton *diagnosis = new QMyButton(this);
    diagnosis->move(510,350);
    diagnosis->setFixedSize(130,60);
    diagnosis->setText("问诊");

    //设置当前日历禁用日期
    //已知姓名str_name和科室id


    //提交预约信息后
    connect(submit, &QPushButton::clicked, [=](){
        QDate selected_date = calendar->selectedDate();
        qDebug()<<"当前选中"<<selected_date.toString("yyyy-MM-dd");
        //发送信号给数据库获取剩余空位
        //如果为真，弹窗预约成功
        //如果为假，弹窗余号不足
        int temp = 0;
        if (temp == 1) {
                    // 显示预约成功消息框
                    QMessageBox::information(nullptr, "消息", "预约成功");
                } else {
                    // 显示预约失败消息框
                    QMessageBox::critical(nullptr, "消息", "余号不足");
                }
    });

    //提交问诊请求后
    connect(diagnosis, &QPushButton::clicked, [=](){
        //跳转到问诊界面


        qDebug()<<pno<<dno;


        QString temp = "chatNEW %1";
        temp = temp.arg(dno);
        tcpSocket->write(temp.toUtf8().data());


        emit quit();
    });


//    QVBoxLayout *pagelayout = new QVBoxLayout;
//    {
//        QHBoxLayout *toplayout = new QHBoxLayout;
//        {
//            toplayout->addWidget(label_pic);
//            toplayout->setStretchFactor(toplayout, 1);

//            toplayout->addWidget(label_info);
//            toplayout->setStretchFactor(label_info, 3);

//        }
//        pagelayout->addLayout(toplayout);
//        pagelayout->setStretchFactor(toplayout, 2);

//        QHBoxLayout *bottomlayout = new QHBoxLayout;
//        {
//            bottomlayout->addWidget(calendar);
//            bottomlayout->setStretchFactor(calendar, 3);

//            bottomlayout->addStretch(1);

//            QVBoxLayout *buttonlayout = new QVBoxLayout;
//            {
//                buttonlayout->addStretch(1);

//                buttonlayout->addWidget(submit);
//                buttonlayout->setStretchFactor(submit, 1);

//                buttonlayout->addStretch(1);

//                buttonlayout->addWidget(diagnosis);
//                buttonlayout->setStretchFactor(diagnosis, 1);

//                buttonlayout->addStretch(1);

//            }

//            bottomlayout->addLayout(buttonlayout);
//            bottomlayout->setStretchFactor(buttonlayout, 1);

//            bottomlayout->addStretch(1);
//        }
//        pagelayout->addLayout(bottomlayout);
//        pagelayout->setStretchFactor(bottomlayout, 10);
//    }
//    this->setLayout(pagelayout);

}
void QMyWidget::setInfo(QString str_info){
    label_info->label_text->setText(str_info);
}
