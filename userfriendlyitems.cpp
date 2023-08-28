#include "userfriendlyitems.h"
#include "ui_userfriendlyitems.h"

UserFriendlyItems::UserFriendlyItems(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserFriendlyItems)
{
    ui->setupUi(this);
}

UserFriendlyItems::~UserFriendlyItems()
{
    delete ui;
}





//圆角按钮的源文件
RoundedRectButton::RoundedRectButton(QWidget *parent) :
    QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFlat(true);  // 设置按钮为无边框
    setMinimumSize(200, 70);  // 设置按钮最小尺寸
    setFont(QFont("Arial", 25));  // 设置字体大小
}

void RoundedRectButton::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    // 创建绘制路径
    QPainterPath path;
//    int r = width();
//    path.moveTo(0, 0);
//    path.arcTo(-r, 0, 2*r, 2*r, 90, -90);
//    path.lineTo(r, height() - r);
//    path.arcTo(-r, height() - 2 * r, 2 * r, 2 * r, 0, -90);
    int radius = height() / 2;  // 半圆的半径
    path.moveTo(radius, 0);  // 左上角uj
    path.lineTo(width() - radius, 0);  // 上边长方形
    path.arcTo(width() - 2 * radius, 0, 2 * radius, 2 * radius, 90, -180);  // 右上半圆
    path.lineTo(radius, height());  // 下边长方形
    path.arcTo(0, 0, 2 * radius, 2 * radius, -90, -180);  // 左下半圆
    path.closeSubpath();

    // 设置按钮的背景
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipPath(path);
    painter->fillRect(rect(), QColor(29, 115, 215));

    //    设置文本
    painter->setPen(QColor(0, 0, 0));  // 设置字体颜色为黑色
    painter->setFont(QFont("Arial", 36));  // 设置字体大小
    QRect textRect = rect().adjusted(5, 5, -5, -5);  // 调整文本矩形以防止与边界重叠
    painter->drawText(textRect, Qt::AlignCenter, text());  // 在中心位置绘制文本

    painter->end();
}

void RoundedRectButton::mousePressEvent(QMouseEvent *event)
{
    animateClick();  // 执行按钮点击的动画效果
    QPushButton::mousePressEvent(event);  // 调用父类方法处理事件
}

void RoundedRectButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);  // 调用父类方法处理事件
}

void RoundedRectButton::animateClick()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setKeyValueAt(0, geometry());
    animation->setKeyValueAt(0.5, geometry().adjusted(-5, -5, 5, 5));
    animation->setKeyValueAt(1, geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}





//导航栏组件按钮

EdgeButton::EdgeButton(QWidget *parent) :
    QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFlat(true);  // 设置按钮为无边框
    setFixedWidth(10);
    setFont(QFont("Arial", 25));  // 设置字体大小
}

void EdgeButton::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    // 创建绘制路径
    QPainterPath path;
    int radius = width();  // 半圆的半径
    path.moveTo(radius, 0);  // 左上角uj
    path.lineTo(width() - radius, 0);  // 上边长方形
    path.arcTo(width() - 2 * radius, 0, 2 * radius, 2 * radius, 90, -180);  // 右上半圆
    path.lineTo(radius, height());  // 下边长方形
    path.arcTo(0, 0, 2 * radius, 2 * radius, -90, -180);  // 左下半圆
    path.closeSubpath();

    // 设置按钮的背景
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipPath(path);
    painter->fillRect(rect(), QColor(0, 100, 200));  // 橙色背景

    //    设置文本
    painter->setPen(QColor(0, 0, 0));  // 设置字体颜色为黑色
    painter->setFont(QFont("Arial", 36));  // 设置字体大小
    QRect textRect = rect().adjusted(5, 5, -5, -5);  // 调整文本矩形以防止与边界重叠
    painter->drawText(textRect, Qt::AlignCenter, text());  // 在中心位置绘制文本

    painter->end();
}

void EdgeButton::mousePressEvent(QMouseEvent *event)
{
    animateClick();  // 执行按钮点击的动画效果
    QPushButton::mousePressEvent(event);  // 调用父类方法处理事件
}

void EdgeButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);  // 调用父类方法处理事件
}

void EdgeButton::animateClick()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setKeyValueAt(0, geometry());
    animation->setKeyValueAt(0.5, geometry().adjusted(-5, -5, 5, 5));
    animation->setKeyValueAt(1, geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}





//导航栏组件
CustomNavigationBar::CustomNavigationBar(QStackedWidget *stackedWidget, QFrame *parent)
    : QFrame(parent)
{

    // 初始化设置
    this->stackedWidget = stackedWidget;
    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFixedWidth(50);

    // 添加导航按钮
    RoundedRectButton *to_DoctorPage = new RoundedRectButton;
    RoundedRectButton *to_onlineChat = new RoundedRectButton;
    RoundedRectButton *to_EditInformation = new RoundedRectButton;
    to_DoctorPage->setText("挂号处理");
    to_onlineChat->setText("线上问诊");
    to_EditInformation->setText("修改信息");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(to_DoctorPage);
    layout->addWidget(to_onlineChat);
    layout->addWidget(to_EditInformation);
    setLayout(layout);

    // 添加阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10); // 设置阴影模糊半径
    shadowEffect->setOffset(0, 5);   // 设置阴影偏移
    setGraphicsEffect(shadowEffect);

//    创建三个页面并插入队列中
    connect(to_DoctorPage, &QPushButton::clicked, this, [=] {
        stackedWidget->setCurrentIndex(0);
    });

    connect(to_onlineChat, &QPushButton::clicked, this, [=] {
        stackedWidget->setCurrentIndex(1);
    });

    connect(to_EditInformation, &QPushButton::clicked, this, [=] {
        stackedWidget->setCurrentIndex(2);
    });
}





//挂号按钮的源文件
RegistrationButton::RegistrationButton(QWidget *parent) :
    QPushButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFlat(true);  // 设置按钮为无边框
    setMinimumSize(100, 150);  // 设置按钮最小尺寸
//    setFont(QFont("Arial", 20));  // 设置字体大小
}

void RegistrationButton::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    // 创建绘制路径
    QPainterPath path;
    int radius = width() / 4;  // 半圆的半径
    path.moveTo(radius, radius);  // 左上角uj
    path.arcTo(0, 0, 2 * radius, 2 * radius, 180, -90);  //左上角圆
    path.lineTo(width() - radius, 0);  // 上边长方形
    path.arcTo(width() - 2 * radius, 0, 2 * radius, 2 * radius, 90, -90);  // 右上角圆
    path.lineTo(width(), height() - radius);  // 下边长方形
    path.arcTo(width() - 2 * radius, height() - 2 * radius, 2 * radius, 2 * radius, 0, -90);  // 左下半圆
    path.lineTo(radius, height());  // 上边长方形
    path.arcTo(0, height() - 2 * radius, 2 * radius, 2 * radius, 270, -90);  // 右上半圆
    path.lineTo(0, radius);  // 下边长方形
    path.closeSubpath();

    // 设置按钮的背景
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setClipPath(path);
    painter->fillRect(rect(), QColor(211, 230, 245));

    //    设置文本
    painter->setPen(QColor(0, 0, 0));  // 设置字体颜色为黑色
    painter->setFont(QFont("Arial", 36));  // 设置字体大小
    QRect textRect = rect().adjusted(5, 5, -5, -5);  // 调整文本矩形以防止与边界重叠
    painter->drawText(textRect, Qt::AlignCenter, text());  // 在中心位置绘制文本

    painter->end();
}

void RegistrationButton::mousePressEvent(QMouseEvent *event)
{
    animateClick();  // 执行按钮点击的动画效果
    QPushButton::mousePressEvent(event);  // 调用父类方法处理事件
}

void RegistrationButton::mouseReleaseEvent(QMouseEvent *event)
{
    QPushButton::mouseReleaseEvent(event);  // 调用父类方法处理事件
}

void RegistrationButton::animateClick()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setKeyValueAt(0, geometry());
    animation->setKeyValueAt(0.5, geometry().adjusted(-5, -5, 5, 5));
    animation->setKeyValueAt(1, geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

