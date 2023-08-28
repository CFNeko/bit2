#ifndef USERFRIENDLYITEMS_H
#define USERFRIENDLYITEMS_H

#include <QWidget>
#include<QPushButton>
#include<QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include<QFrame>
#include <QGraphicsDropShadowEffect>
#include <QStackedWidget>

namespace Ui {
class UserFriendlyItems;
}

class UserFriendlyItems : public QWidget
{
    Q_OBJECT

public:
    explicit UserFriendlyItems(QWidget *parent = nullptr);
    ~UserFriendlyItems();

private:
    Ui::UserFriendlyItems *ui;
};




//圆角按钮组件
class RoundedRectButton : public QPushButton
{
public:
    explicit RoundedRectButton(QWidget *parent = nullptr);
    ~RoundedRectButton() {};
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void animateClick();
};



//导航栏按钮组件
class EdgeButton : public QPushButton
{
public:
    explicit EdgeButton(QWidget *parent = nullptr);
    ~EdgeButton() {};
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void animateClick();
};



//导航栏组件
class CustomNavigationBar : public QFrame
{
    Q_OBJECT
public:
    explicit CustomNavigationBar(QStackedWidget *stackedWidget, QFrame *parent = nullptr);
    ~CustomNavigationBar() {};
private:
    QStackedWidget *stackedWidget;
};





//挂号界面的按钮
class RegistrationButton : public QPushButton
{
public:
    explicit RegistrationButton(QWidget *parent = nullptr);
    ~RegistrationButton() {};
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void animateClick();
};

#endif // USERFRIENDLYITEMS_H
