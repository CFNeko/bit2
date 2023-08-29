#include "mainwidget.h"
#include "ui_mainwidget.h"

int id = -1;
mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    //让主窗口居中显示
    QList<QScreen*> screens = QGuiApplication::screens();
        if (!screens.isEmpty()) {
            QScreen *primaryScreen = screens[0]; // 获取主屏幕信息
            QRect mainScreenSize = primaryScreen->geometry();
            int screenWidth = mainScreenSize.width();
            int screenHeight = mainScreenSize.height();
            // 计算主窗口的位置，使其居中
            int windowWidth = 800; // 设置主窗口的宽度
            int windowHeight = 640; // 设置主窗口的高度
            int x = (screenWidth - windowWidth) / 2;
            int y = (screenHeight - windowHeight) / 2;
            // 设置主窗口的位置
            this->setGeometry(x, y, windowWidth, windowHeight);
        }
    //大致框架的大小
    this->setFixedSize(800,640);
    ui->sidebar->setFixedSize(110,560);
    ui->stackedWidget->setFixedSize(690,560);
    ui->title->setFixedSize(800,80);

    //连接toolbutton和stackedwidget间的索引
    QButtonGroup *btnGroup = new QButtonGroup();
    btnGroup->addButton(ui->room0, 0);
    btnGroup->addButton(ui->room1, 1);
    btnGroup->addButton(ui->room2, 2);
    btnGroup->addButton(ui->room3, 3);
    btnGroup->addButton(ui->room4, 4);
    btnGroup->addButton(ui->room5, 5);
    btnGroup->addButton(ui->room6, 6);
    btnGroup->addButton(ui->room7, 7);
    btnGroup->addButton(ui->room8, 8);
    btnGroup->addButton(ui->room9, 9);
    connect(btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    //设置默认Tab为第一个,Button为第一个
//    ui->room0->setChecked(true);
    int temp_int = ui->stackedWidget->currentIndex();
    if(temp_int != 10 )
        ui->stackedWidget->setCurrentIndex(10);
    ui->tabWidget_0->setCurrentIndex(0);
    ui->tabWidget_1->setCurrentIndex(0);
    ui->tabWidget_2->setCurrentIndex(0);
    ui->tabWidget_3->setCurrentIndex(0);
    ui->tabWidget_4->setCurrentIndex(0);
    ui->tabWidget_5->setCurrentIndex(0);
    ui->tabWidget_6->setCurrentIndex(0);
    ui->tabWidget_7->setCurrentIndex(0);
    ui->tabWidget_8->setCurrentIndex(0);
    ui->tabWidget_9->setCurrentIndex(0);

        //测试代码
        //1、获取button id，以得到当前科室名称
        QObject::connect(btnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), [=]() {
                id = ui->stackedWidget->currentIndex();
                QString str_temp = "tabWidget_" + QString::number(id);
                //获取到当前所指qwidget的指针
                QWidget *qtWidget = ui->stackedWidget->currentWidget();
                //获取到当前所指tabwidget的指针
                QTabWidget* tabWidget = qtWidget->findChild<QTabWidget*>(str_temp);

                //导入医生信息
//                while(0){
                    QString str_name = "新医生";
                    QString str_info;
                    QMyWidget *tempwidget = new QMyWidget(str_name, id, nullptr);
                    tabWidget->addTab(tempwidget, str_name);
                    tempwidget->setInfo(str_info);
                    tempwidget->tcpSocket = tcpSocket;
                    tempwidget->pno = pno;

                    /*
                     * 我需要获取医生编号
                    */
                    tempwidget->dno = 1234;
                    connect(tempwidget,&QMyWidget::quit,this,&mainWidget::chat);
                    connect(tempwidget,&QMyWidget::quit,this,&QWidget::close);
//                }

            });
        //遍历当前科室的所有医生，增加医生到stackedwidget的对应page；


//        连接退出按钮
        connect(ui->pushButton, &QPushButton::clicked, this, &mainWidget::mClosed);
        connect(ui->pushButton, &QPushButton::clicked, this, &QWidget::close);
}
mainWidget::~mainWidget()
{
    delete ui;
}

