/********************************************************************************
** Form generated from reading UI file 'msgitem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGITEM_H
#define UI_MSGITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgItem
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widgetMain;
    QWidget *widgetHead;
    QWidget *widgetCount;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbCount;
    QLabel *lbName;
    QLabel *lbMsg;
    QLabel *lbTime;
    QPushButton *btnClose;

    void setupUi(QWidget *MsgItem)
    {
        if (MsgItem->objectName().isEmpty())
            MsgItem->setObjectName(QString::fromUtf8("MsgItem"));
        MsgItem->resize(360, 70);
        MsgItem->setMinimumSize(QSize(360, 70));
        MsgItem->setMaximumSize(QSize(360, 70));
        horizontalLayout = new QHBoxLayout(MsgItem);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widgetMain = new QWidget(MsgItem);
        widgetMain->setObjectName(QString::fromUtf8("widgetMain"));
        widgetMain->setMinimumSize(QSize(360, 70));
        widgetMain->setMaximumSize(QSize(360, 70));
        widgetMain->setStyleSheet(QString::fromUtf8("QWidget#widgetMain{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border-bottom: 1px solid #F2F2F2;\n"
"}\n"
"\n"
""));
        widgetHead = new QWidget(widgetMain);
        widgetHead->setObjectName(QString::fromUtf8("widgetHead"));
        widgetHead->setGeometry(QRect(10, 10, 48, 48));
        widgetHead->setMinimumSize(QSize(48, 48));
        widgetHead->setMaximumSize(QSize(48, 48));
        widgetHead->setStyleSheet(QString::fromUtf8("QWidget#widgetHead{\n"
"	background-color: rgb(0, 0, 0);\n"
"	border-radius: 4px;\n"
"	border-image: url(:/image/Head.png);\n"
"}"));
        widgetCount = new QWidget(widgetMain);
        widgetCount->setObjectName(QString::fromUtf8("widgetCount"));
        widgetCount->setGeometry(QRect(50, 0, 21, 21));
        widgetCount->setMinimumSize(QSize(21, 21));
        widgetCount->setMaximumSize(QSize(21, 21));
        widgetCount->setStyleSheet(QString::fromUtf8("QWidget#widgetCount{\n"
"	border-radius: 10px;\n"
"	background-color: rgb(255, 0, 0);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widgetCount);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lbCount = new QLabel(widgetCount);
        lbCount->setObjectName(QString::fromUtf8("lbCount"));
        lbCount->setStyleSheet(QString::fromUtf8("QLabel#labelCount{\n"
"	color: white;\n"
"	background-color: transparent;\n"
"	font: 10pt \"Airal\";\n"
"}"));
        lbCount->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lbCount);

        lbName = new QLabel(widgetMain);
        lbName->setObjectName(QString::fromUtf8("lbName"));
        lbName->setGeometry(QRect(80, 10, 121, 21));
        lbName->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: transparent;\n"
"	font: 75 14pt \"Arial\";\n"
"	color: #000000\n"
"}"));
        lbMsg = new QLabel(widgetMain);
        lbMsg->setObjectName(QString::fromUtf8("lbMsg"));
        lbMsg->setGeometry(QRect(80, 40, 181, 21));
        lbMsg->setStyleSheet(QString::fromUtf8("QLabel#labelMsg{\n"
"	background-color: transparent;\n"
"	font: 75 11pt \"Arial\";\n"
"	color: #888888;\n"
"}"));
        lbTime = new QLabel(widgetMain);
        lbTime->setObjectName(QString::fromUtf8("lbTime"));
        lbTime->setGeometry(QRect(205, 10, 141, 21));
        lbTime->setStyleSheet(QString::fromUtf8("QLabel#labelTime{\n"
"	background-color: transparent;\n"
"	font: 75 11pt \"Arial\";\n"
"	color: #888888;\n"
"}"));
        btnClose = new QPushButton(widgetMain);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(320, 30, 20, 20));
        btnClose->setStyleSheet(QString::fromUtf8("QPushButton#btnClose{\n"
"	border-radius: 10px;\n"
"	background-color: red\n"
"}"));

        horizontalLayout->addWidget(widgetMain);


        retranslateUi(MsgItem);
        QObject::connect(btnClose, SIGNAL(clicked()), MsgItem, SLOT(on_btnDeleteClicked()));

        QMetaObject::connectSlotsByName(MsgItem);
    } // setupUi

    void retranslateUi(QWidget *MsgItem)
    {
        MsgItem->setWindowTitle(QApplication::translate("MsgItem", "Form", nullptr));
        lbCount->setText(QApplication::translate("MsgItem", "99", nullptr));
        lbName->setText(QApplication::translate("MsgItem", "Karson", nullptr));
        lbMsg->setText(QApplication::translate("MsgItem", "How do you do?", nullptr));
        lbTime->setText(QApplication::translate("MsgItem", "01/01/2015 09:00:00", nullptr));
        btnClose->setText(QApplication::translate("MsgItem", "x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MsgItem: public Ui_MsgItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGITEM_H
