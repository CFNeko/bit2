#include "widget.h"
#include "ui_widget.h"
#include "combobox.h"
#include <QStyledItemDelegate>
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->comboBox->setComboBoxModel(LIST_MODEL);
    ui->comboBox->setItemDelegate(new QStyledItemDelegate(this));
    ui->comboBox_2->setComboBoxModel(TABLE_MODEL);
}

Widget::~Widget()
{
    delete ui;
}
