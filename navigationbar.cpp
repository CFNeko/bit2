#include "navigationbar.h"
#include "ui_navigationbar.h"

NavigationBar::NavigationBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationBar)
{
    ui->setupUi(this);
}

NavigationBar::~NavigationBar()
{
    delete ui;
}
