#include "dbwidget.h"
#include "ui_dbwidget.h"

#include <QTimer>
#include <QDateTime>
#include <QHostAddress>



dbWidget::dbWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dbWidget)
{
    ui->setupUi(this);

    EnterEventFilter *filter =  new EnterEventFilter();
    ui->textEditWrite->installEventFilter(filter);
    connect(filter,&EnterEventFilter::enter,this,&dbWidget::on_pushButtonSend_clicked);
    QScrollBar *bar = ui->chatArea->verticalScrollBar();
    connect(bar, &QScrollBar::rangeChanged,
            [=]()
    {
        bar->setValue(bar->maximum());
    });

    chatWidget = new QWidget();
    chatLayout = new QVBoxLayout(chatWidget);

    ui->pushButtonImg->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);
}

dbWidget::~dbWidget()
{
    delete ui;
}

void dbWidget::showMessage(message *m)
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addItem(new QSpacerItem(10, 100));
    layout->addWidget(m);
    layout->addItem(new QSpacerItem(10, 100));
    chatLayout->addLayout(layout);
}

void dbWidget::sendData()
{
    qint64 len = 0;
    do{
        //每次发送数据的大小
        char buf[4*1024] = {0};
        len = 0;
        //往文件中读数据
        len = file->read(buf, sizeof(buf));
        //发送数据，读多少，发多少
        len = tcpSocket->write(buf, len);
    }while(len > 0);
    file->close();
    qDebug()<<"图片发送完成";
}

void dbWidget::on_pushButtonSend_clicked()
{
    QString info = ui->textEditWrite->toPlainText();

    QString str = "message ";
    str+=author;
    str+=" ";
    str+= QString::number(pno);
    str+=" ";
    str+= QString::number(dno);
    str+=" ";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString time = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    str+=time;
    str+=" ";

    str+=info;


    qDebug()<<str;
    //写入套接字
    tcpSocket->write(str.toUtf8().data());
    //写入接收区
    this->showMessage(new message(info,
                                  time,
                                  author,
                                  QByteArray(),
                                  author,chatWidget));


    //清除界面发送区
    ui->textEditWrite->clear();

}

void dbWidget::on_pushButtonImg_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                    "open", "/home", "Image(*.jpg *.png)");

    QFileInfo info(path);
    int fileSize = info.size();

    file = new QFile(path);
    if (file->open(QIODevice::ReadOnly)) {

        QString str = "image ";
        str+=author;
        str+=" ";
        str+= QString::number(pno);
        str+=" ";
        str+= QString::number(dno);
        str+=" ";
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString time = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        str+=time;
        str+=" ";

        str += QString::number(fileSize);
        qDebug()<<str;
        //写入套接字
        tcpSocket->write(str.toUtf8().data());

        QTimer *timer = new QTimer;
        timer->start(20);
        connect(timer, &QTimer::timeout,
                [=]()
        {
            //关闭定时器
            timer->stop();
            //发送文件
            sendData();

        });

        //写入接收区
        QByteArray imageData = file->readAll();
        file->seek(0);
        this->showMessage(new message("",
                                      time,
                                      author,
                                      imageData,
                                      author,chatWidget));

    }else{
        qDebug() << "Failed to open image file";
    }


}

void dbWidget::reLoad()
{
    chatWidget->hide();

    chatWidget = new QWidget();
    chatLayout = new QVBoxLayout(chatWidget);

    ui->chatArea->setWidgetResizable(true);
    ui->chatArea->setWidget(chatWidget);
    chatWidget->setLayout(chatLayout);


//    qDebug()<<pno<<dno;

    ui->pushButtonImg->setEnabled(true);
    ui->pushButtonSend->setEnabled(true);
}
