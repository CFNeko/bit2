#include "status_bar_widget.h"
#include "ui_status_bar_widget.h"

StatusBarWidget::StatusBarWidget(QWidget *parent) : QWidget(parent), ui(new Ui::StatusBarWidget)
{
    ui->setupUi(this);
}

StatusBarWidget::~StatusBarWidget()
{
    delete ui;
}
