#include "testwidget.h"
#include "ui_testwidget.h"

#include "globalapplication.h"

#include <QDialog>

TestWidget::TestWidget(QWidget *parent) : BaseWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
}

TestWidget::~TestWidget()
{
    delete ui;
}

bool TestWidget::saveRequest()
{
    //to do something...
    return true;
}

void TestWidget::on_pushButton_clicked()
{
    if(ui->pushButton->isChecked())
    {
        app->switchApplicationLanguage(GlobalApplication::LANGUAGE_ENGLISH);
        return;
    }
    app->switchApplicationLanguage(GlobalApplication::LANGUAGE_SIMPLE_CN);
}
