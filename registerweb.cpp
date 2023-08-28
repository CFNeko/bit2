#include "registerweb.h"
#include "ui_registerweb.h"
#include<QPainter>
#include<QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QMainWindow>
#include<QFormLayout>
#include<QRadioButton>
#include <QDebug>
#include <QSqlQuery>
#include<QButtonGroup>


#define Path_to_DB "/home/user/Qtworks/mainWindow/2/database.db"

RegisterWeb::RegisterWeb(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWeb)
{
    ui->setupUi(this);
    homePage = new HomePage();
    signUp = new SignUp();
    //db
    myDB = QSqlDatabase::addDatabase("QSQLITE");
        myDB.setDatabaseName(Path_to_DB);
        QFileInfo checkFile(Path_to_DB);
        if (myDB.open()) {
                qDebug() << "DB online";
        }
        else {
                qDebug("DB no online :(");
                QMessageBox::warning(this, "error", myDB.lastError().text());
        }

    //1.添加资源文件

   //2.指定窗口大小--固定大小
   this->setFixedSize(900,600);

   //3.设置窗口左上角图标[这个功能没有实现]
   this->setWindowIcon(QIcon(":/resource111/1.png"));

   //4.设置窗口标题
   this->setWindowTitle("智慧医疗管理系统");

   //5.加载背景图片--重写画图事件函数
   //详见绘图事件函数中


   //6.在ui文件中添加工具栏，并将其他无用部分删除

   //7.登录页面实现
    //创建用户名和密码的标签和文本框

           QLabel *usernameLabel = new QLabel("Username:");
           QFont font("Arial", 18, QFont::Bold);
           usernameLabel->setFont(font);
           usernameLabel->setStyleSheet("color: white;");
           QLineEdit *usernameLineEdit = new QLineEdit;
           usernameLineEdit->setPlaceholderText("Enter text...");
           usernameLineEdit->setMinimumWidth(200);  // 设置最小宽度为300像素
           usernameLineEdit->setMinimumHeight(50);

           QLabel *passwordLabel = new QLabel("Password:");
           passwordLabel->setFont(font);
           passwordLabel->setStyleSheet("color: white;");
           QLineEdit *passwordLineEdit = new QLineEdit;
           passwordLineEdit->setMinimumWidth(200);
           passwordLineEdit->setMinimumHeight(50);
           passwordLineEdit->setEchoMode(QLineEdit::Password); // 设置密码输入框的显示模式
           passwordLineEdit->setMaxLength(20); // 设置最大长度为 20 个字符

           // 创建登录按钮
           QPushButton *loginButton = new QPushButton("Login");
           QPushButton *registerButton = new QPushButton("Register");

          // pushButton_patient->move(100,350);
          // pushButton_doctor->move(250,350);




          //    connect(pushButton_patient,&QPushButton::pressed,this,&RegisterWeb::on_click




           connect(registerButton, &QPushButton::clicked,
                   [=](){

           this->close();
           signUp->show();
           });

//           connect(loginButton, &QPushButton::clicked, this, &RegisterWeb::login);
           connect(loginButton, &QPushButton::clicked,
                            [=](){

                       QString str = usernameLineEdit->text();
                       QString password = passwordLineEdit->text();
                       QString temp = "SELECT * FROM patient WHERE name= '" + str + "' and password='" + password + "'";
                       myDB.open();
                       QSqlQuery q;
                       QString data = "";
                       q.exec(temp);
                        while (q.next()) {
                            data += q.value(0).toString() + q.value(1).toString();
                        }
                        if (data > 0) {                       

                            this->hide();
                            homePage->show();
                       }
                        else {
                            //Jenny 请假一个错误widget
                            passwordLineEdit->setText("");
                            showMessageBox();
                        }
                         });
           QHBoxLayout* horizontalLayout = new QHBoxLayout; // 创建水平布局
           horizontalLayout->addWidget(registerButton); // 将按键1添加到水平布局
           horizontalLayout->addWidget(loginButton); // 将按键2添加到水平布局


          // 创建右侧布局，并将用户名、密码和登录按钮添加到布局中
           QVBoxLayout *rightLayout = new QVBoxLayout;
           rightLayout->setContentsMargins(500, 100, 50, 100);
           rightLayout->setSpacing(50); // 设置部件之间的间距

           rightLayout->addWidget(usernameLabel);
           rightLayout->addWidget(usernameLineEdit);
           rightLayout->addWidget(passwordLabel);
           rightLayout->addWidget(passwordLineEdit);
           rightLayout->addLayout(horizontalLayout);
           rightLayout->addStretch(500); // 可选：添加一个伸缩项，使布局靠上


           //创造一个主布局
           QVBoxLayout *mainLayout = new QVBoxLayout;
           mainLayout->addStretch(); // 可选：添加一个伸缩项，使布局靠左
           mainLayout->addLayout(rightLayout);


           // 创建主窗口部件，并设置布局
           QWidget *centralWidget = new QWidget;
           centralWidget->setLayout(mainLayout);
           setCentralWidget(centralWidget);


           // 创建两个单选按钮
        QRadioButton* pushButton_patient = new QRadioButton("Patient",centralWidget);
        QRadioButton* pushButton_doctor = new QRadioButton("Doctor",centralWidget);

        pushButton_patient->setStyleSheet(
                    "QRadioButton {"
                                                    "    background-color: rgba(255, 255, 255, 0.5);"  // 半透明的白色背景
                                                    "    color: #000000;"
                                                    "    border: none;"
                                                    "    border-radius: 5px;"
                                                    "    padding: 5px;"
                                                    "}"
                                                    "QRadioButton::indicator {"
                                                    "    width: 16px;"
                                                    "    height: 16px;"
                                                    "}"
                                                    "QRadioButton::indicator:checked {"
                                                    "    background-color: #0000ff;"  // RGB(13, 175, 216)背景
                                                    "}"
                    );
        pushButton_doctor->setStyleSheet(
                    "QRadioButton {"
                                                    "    background-color: rgba(255, 255, 255, 0.5);"  // 半透明的白色背景
                                                    "    color: #000000;"
                                                    "    border: none;"
                                                    "    border-radius: 5px;"
                                                    "    padding: 5px;"
                                                    "}"
                                                    "QRadioButton::indicator {"
                                                    "    width: 16px;"
                                                    "    height: 16px;"
                                                    "}"
                                                    "QRadioButton::indicator:checked {"
                                                    "    background-color: #0000ff;"  // RGB(13, 175, 216)背景
                                                    "}"
                    );

           // 创建按钮组，并将单选按钮添加到组中
           QButtonGroup radiobuttonGroup;
           radiobuttonGroup.addButton(pushButton_patient);
           radiobuttonGroup.addButton(pushButton_doctor);
           // 设置按钮组为互斥的，即只能选择一个选项
           radiobuttonGroup.setExclusive(true);


           // 将单选按钮添加到布局中
           pushButton_patient->move(100,400);
           pushButton_doctor->move(300,400);

           connect(signUp, SIGNAL(signalToMain()), this, SLOT(on_exit_Signal_Received()) );
           connect(signUp, SIGNAL(signalTologin()), this, SLOT(on_exit_Signal_Received()) );
}

RegisterWeb::~RegisterWeb()
{
    delete ui;
}

//重写绘图函数--声明作用域，不然会被编译为全局函数
//头文件--<QPainter>
void RegisterWeb::paintEvent(QPaintEvent*)
{
    QPainter painter1;
    painter1.begin(this);
    QPixmap pixmap1;
    pixmap1.load(":/resource111/1.png");
    painter1.drawPixmap(0,0,this->width(),this->height(),pixmap1);

    QPixmap logoPixmap;
    logoPixmap.load(":/resource111/logo.jpg");
    logoPixmap = logoPixmap.scaled(logoPixmap.width()*0.2, logoPixmap.height()*0.2);
    painter1.drawPixmap(180,60,logoPixmap);

    // 添加标题
    QFont titleFont("Arial", 20, QFont::Bold);

    painter1.setFont(titleFont);
    painter1.drawText(QRect(0, logoPixmap.height()+80, this->width()*0.5, 40), Qt::AlignCenter, "欢迎来到智慧医疗管理系统");


}

void RegisterWeb::on_exit_Signal_Received()
{
    this->show();
    signUp->close();
}

void RegisterWeb::handleMessageBoxFinished(int result)
{
    if (messageBox != nullptr)
            {
                messageBox->deleteLater();
                messageBox = nullptr;
            }
}

void RegisterWeb::showMessageBox()
{
    if (messageBox == nullptr)
            {
                messageBox = new QMessageBox(this);
                messageBox->setWindowTitle("提示"); // 设置标题文字
                messageBox->setText("用户名不存在或者密码错误！");
                messageBox->setStandardButtons(QMessageBox::Ok);
                connect(messageBox, &QMessageBox::finished, this, &RegisterWeb::handleMessageBoxFinished);
                messageBox->show();
            }
}
