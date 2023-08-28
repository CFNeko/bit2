#include "navigationdesign.h"
#include "ui_navigationdesign.h"

navigationDesign::navigationDesign(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::navigationDesign)
{
    ui->setupUi(this);
}

navigationDesign::~navigationDesign()
{
    delete ui;
}

