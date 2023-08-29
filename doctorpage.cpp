#include "doctorpage.h"
#include "ui_doctorpage.h"

DoctorPage::DoctorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorPage)
{
    ui->setupUi(this);
    ui->Homepge->setStyleSheet(
                "QTabWidget::pane{ border:none; }"
                "QTabWidget::tab-bar{ alignment:left; }"
                "QTabBar::tab{ background:transparent; color:green; min-width:30ex; min-height:10ex; }"
                "QTabBar::tab:hover{ background:rgb(255, 255, 255, 100); }"
                "QTabBar::tab:selected{ border-color: white; background:white; color:green; }"
                );
    ui->frame->setStyleSheet(
                "background-color: rgba(255, 255, 255, 128);"
                );
    ui->registration_inquiry->setFixedSize(100,100);
    ui->registration_history->setFixedSize(100,100);
    QVBoxLayout* layout = new QVBoxLayout(ui->scrollAreaWidgetContents); // 创建垂直布局
    layout->setSpacing(10); // 设置布局的间距

    setWindowTitle("医生端主页");

    // 创建水平布局管理器
    QHBoxLayout *mainlayout = new QHBoxLayout;

    // 创建 QLabel 控件并设置图片
    QLabel *imageLabel1 = new QLabel;
    QPixmap pixmap1(":/resource111/1.png"); // 设置图片的路径和文件名
    imageLabel1->setPixmap(pixmap1);
    imageLabel1->setScaledContents(true); // 自适应大小

    QLabel *imageLabel2 = new QLabel;
    QPixmap pixmap2(":/resource111/1.png");
    imageLabel2->setPixmap(pixmap2);
    imageLabel2->setScaledContents(true);

    // 将 QLabel 控件添加到布局管理器
    mainlayout->addWidget(imageLabel1);
    mainlayout->addWidget(imageLabel2);

    ui->frame_5->setLayout(mainlayout);

    //       跳转函数
    connect(ui->registration_inquiry, &QPushButton::clicked, this, [=]
    {
        RegistraitonDoctorPage *r = new RegistraitonDoctorPage(nullptr, false);
        r->show();
        this->hide();
        connect(r, &RegistraitonDoctorPage::rClosed, this, &QWidget::show);
    });

    connect(ui->registration_history, &QPushButton::clicked, this, [=]
    {
        RegistraitonDoctorPage *r = new RegistraitonDoctorPage(nullptr, true);
        r->show();
        this->hide();
        connect(r, &RegistraitonDoctorPage::rClosed, this, &QWidget::show);
    });


    //在线问诊
    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/chat/msg.wav"));

    myList = new QList<int>;
    myButtonList =new QList<QPushButton*>;


    //设置医生号
    dno = 1234;
    author = "doctor";


    tcpSocket = new QTcpSocket(this);
    imageMode = false;

    ui->mainChat->tcpSocket = tcpSocket;
    ui->mainChat->dno = dno;
    ui->mainChat->author = author;

    //设置服务器IP和PORT
    QString ip = "127.0.0.1";
    qint16 port = 8888;
    //向服务器发起连接请求
    tcpSocket->connectToHost(QHostAddress(ip),port);


    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
    {
        QString str = "login doctor %1";
        str = str.arg(dno);
        tcpSocket->write(str.toUtf8().data());;
    });

    connect(tcpSocket,&QTcpSocket::readyRead,this,&DoctorPage::on_tcpSocket_readyRead);



}

DoctorPage::~DoctorPage()
{
    delete ui;
}

void DoctorPage::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/background.jpg");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);
}


void DoctorPage::addCustomWidget()
{
    QTextEdit* customWidget = new QTextEdit(ui->scrollAreaWidgetContents); // 创建自定义界面部件
    customWidget->setText("Title");

    customWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 设置大小策略
    ui->scrollAreaWidgetContents->layout()->addWidget(customWidget); // 将自定义界面部件添加到垂直布局中

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
}

void DoctorPage::on_tcpSocket_readyRead()
{
    if(this->imageMode){
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
    }else{
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
            qDebug()<<"收到患者回信"<<strlist[1];
            player->play();

            QPushButton *button = NULL;
            for (int i=0;i<myList->length();i++) {
                if(myList->at(i) == strlist[1].toInt()){
                    button = myButtonList->at(i);
                    break;
                }
            }
            if(button==NULL){
                //new Button
                int pno = strlist[1].toInt();
                /*
                 * 我需要通过患者uid得到患者姓名
                */
                QString pname = QString::number(pno);
                button = new QPushButton(pname);
                button->setFixedHeight(70);
                connect(button,&QPushButton::clicked,
                        [=]()
                {
                    ui->mainChat->pno = pno;
                    QString str = "chat doctor %1 %2";
                    str = str.arg(pno).arg(dno);
                    tcpSocket->write(str.toUtf8().data());;
                    ui->labelName->setText(pname);
                    ui->mainChat->reLoad();
                    button->setStyleSheet("");
                });
                ui->msgWidget->layout()->addWidget(button);
            }
            //标红变色
            button->setStyleSheet("background-color: red;");

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
            for (int i=1;i<newlist.length()-1;i++) {
                qDebug()<<"收到患者回信"<<newlist[i];
                player->play();
            }
            QStringList chatlist = loadlist[1].split(" ");
            for (int i=1;i<chatlist.length();i++) {
                qDebug()<<"消息列表"<<chatlist[i];
                //new Button
                int pno = chatlist[i].toInt();
                /*
                 * 我需要通过患者uid得到患者姓名
                */
                QString pname = QString::number(pno);
                QPushButton *button = new QPushButton(pname);
                button->setFixedHeight(70);
                connect(button,&QPushButton::clicked,
                        [=]()
                {
                    ui->mainChat->pno = pno;
                    QString str = "chat doctor %1 %2";
                    str = str.arg(pno).arg(dno);
                    tcpSocket->write(str.toUtf8().data());;
                    ui->labelName->setText(pname);
                    ui->mainChat->reLoad();
                    button->setStyleSheet("");
                });

                for (int j=1;j<newlist.length()-1;j++) {
                    if(chatlist[i] == newlist[j]){
                        button->setStyleSheet("background-color: red;");
                        break;
                    }
                }
                myList->append(pno);
                myButtonList->append(button);
                ui->msgWidget->layout()->addWidget(button);
            }
        }
    }
}
