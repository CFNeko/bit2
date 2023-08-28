#include "operate_button.h"


OperateButton::OperateButton(QString text, QWidget *parent) : QPushButton(parent)
{
	setText(text);
	this->setProperty("type", "operate");
}

OperateButton::~OperateButton()
{

}

void OperateButton::enterEvent(QEvent *e)
{
	setCursor(Qt::PointingHandCursor);
	QPushButton::enterEvent(e);
}

void OperateButton::leaveEvent(QEvent *e)
{
	QPushButton::leaveEvent(e);
}

