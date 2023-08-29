#include "qmybutton.h"

QMyButton::QMyButton(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet(
            "QPushButton{"
            "    background-color: rgb(134, 183, 200);"
            "    border: 2px solid rgb(95,146,178);"
            "    border-radius: 30px; /* 将圆角半径设置为按钮宽度的一半 */"
            "    color: white;"
            "    font-size: 16px;"
            "}"
            "QPushButton:hover {"
            "    background-color: rgb(0, 130, 150);"
            "    border: 2px solid rgb(95,146,178);"
            "    border-radius: 30px; /* 将圆角半径设置为按钮宽度的一半 */"
            "    color: white;"
            "}"
            "QPushButton:pressed{"
            "    background-color: rgb(85, 170, 255);"
            "    border: 2px solid rgb(60,128,177);"
            "    border-radius: 30px; /* 将圆角半径设置为按钮宽度的一半 */"
            "    color: white;"
            "}"
        );
    //设置问诊按钮
}
