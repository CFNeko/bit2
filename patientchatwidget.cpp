#include "patientchatwidget.h"
#include "ui_patientchatwidget.h"



patientChatWidget::patientChatWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientChatWidget)
{
    ui->setupUi(this);
//    player = new QMediaPlayer;
//    player->setMedia(QUrl("qrc:/music/msg.wav"));

//    pno = 2003;
//    author = "patient";

//    tcpSocket = new QTcpSocket(this);
//    imageMode = false;

//    ui->mainChat->tcpSocket = tcpSocket;
//    ui->mainChat->pno = pno;
//    ui->mainChat->author = author;

//    //设置服务器IP和PORT
//    QString ip = "127.0.0.1";
//    qint16 port = 8888;
//    //向服务器发起连接请求
//    tcpSocket->connectToHost(QHostAddress(ip),port);


//    connect(tcpSocket,&QTcpSocket::connected,
//            [=]()
//    {
//        QString str = "login patient %1";
//        str = str.arg(pno);
//        tcpSocket->write(str.toUtf8().data());;
//    });

//    connect(tcpSocket,&QTcpSocket::readyRead,this,&patientChatWidget::on_tcpSocket_readyRead);
}

patientChatWidget::~patientChatWidget()
{
    delete ui;
}

void patientChatWidget::on_tcpSocket_readyRead()
{
    if(this->imageMode){
//        qDebug()<<"image";
        QByteArray array = tcpSocket->readAll();
        this->imgData->append(array);
        if(this->imgData->size() == this->imgHead[6].toInt()){
            this->imageMode = false;
            ui->mainChat->showMessage(new message("",
                                          imgHead[4]+" "+imgHead[5],
                                          imgHead[1],
                                          *(this->imgData),
                                          author,ui->mainChat->chatWidget));
            player->play();
        }
    }
    else{
        //获取对方发送的内容
        QString str(tcpSocket->readAll());
        QStringList strlist = str.split(" ");

        qDebug()<<str;


        if(strlist[0]=="message"){
            ui->mainChat->showMessage(new message(strlist[6],
                                          strlist[4]+" "+strlist[5],
                                          strlist[1],
                                          QByteArray(),
                                          author,ui->mainChat->chatWidget));
            player->play();

        }
        else if(strlist[0]=="image"){
            this->imageMode = true;
            this->imgData = new QByteArray();
            this->imgHead = strlist;
        }
        else if(strlist[0]=="new"){
            qDebug()<<"收到医生回信"<<strlist[2];
            player->play();
        }
        else if(strlist[0]=="initial"){
            QStringList initiallist = str.split("\n");
            for (int i=1;i<initiallist.length()-1;i++) {
                strlist = initiallist[i].split(" ");
                ui->mainChat->showMessage(new message(strlist[6],
                                              strlist[4]+" "+strlist[5],
                                              strlist[1],
                                              QByteArray(),
                                              author,ui->mainChat->chatWidget));
            }
        }
        else if(strlist[0]=="load"){
            QStringList loadlist = str.split("\n");
            QStringList newlist = loadlist[0].split(" ");
            for (int i=1;i<newlist.length();i++) {
                qDebug()<<"收到医生回信"<<newlist[i];
                player->play();
            }
            QStringList chatlist = loadlist[1].split(" ");
            for (int i=1;i<chatlist.length();i++) {
                qDebug()<<"消息列表"<<chatlist[i];
            }
        }
    }
}

void patientChatWidget::on_doctor1234_clicked()
{
    ui->mainChat->dno = 1234;
    QString str = "chat patient %1 1234";
    str = str.arg(pno);
    tcpSocket->write(str.toUtf8().data());;
    ui->mainChat->reLoad();
}
void patientChatWidget::on_doctor5678_clicked()
{
    ui->mainChat->dno = 5678;
    QString str = "chat patient %1 5678";
    str = str.arg(pno);
    tcpSocket->write(str.toUtf8().data());;
    ui->mainChat->reLoad();
}

