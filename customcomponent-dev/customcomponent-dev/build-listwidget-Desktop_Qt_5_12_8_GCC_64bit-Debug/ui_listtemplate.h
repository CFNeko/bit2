/********************************************************************************
** Form generated from reading UI file 'listtemplate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTTEMPLATE_H
#define UI_LISTTEMPLATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListTemplate
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QListWidget *listWidget;

    void setupUi(QWidget *ListTemplate)
    {
        if (ListTemplate->objectName().isEmpty())
            ListTemplate->setObjectName(QString::fromUtf8("ListTemplate"));
        ListTemplate->resize(362, 498);
        horizontalLayout_2 = new QHBoxLayout(ListTemplate);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 20, 0, 0);
        widget = new QWidget(ListTemplate);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAdd = new QPushButton(widget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setMinimumSize(QSize(26, 26));
        btnAdd->setMaximumSize(QSize(26, 26));

        horizontalLayout->addWidget(btnAdd);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMinimumSize(QSize(360, 0));
        listWidget->setMaximumSize(QSize(360, 16777215));

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout_2->addWidget(widget);


        retranslateUi(ListTemplate);
        QObject::connect(btnAdd, SIGNAL(clicked()), ListTemplate, SLOT(on_btnAddClicked()));
        QObject::connect(listWidget, SIGNAL(itemClicked(QListWidgetItem*)), ListTemplate, SLOT(on_listWidgetClicked(QListWidgetItem*)));

        QMetaObject::connectSlotsByName(ListTemplate);
    } // setupUi

    void retranslateUi(QWidget *ListTemplate)
    {
        ListTemplate->setWindowTitle(QApplication::translate("ListTemplate", "ListTemplate", nullptr));
        btnAdd->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ListTemplate: public Ui_ListTemplate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTTEMPLATE_H
