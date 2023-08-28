#include "button_number.h"
#include <QStyle>
ButtonNumber::ButtonNumber(QWidget* parent) : QPushButton(parent)
{

}

ButtonNumber::ButtonNumber(int id, QWidget* parent) : QPushButton(parent), m_id(id)
{

}

ButtonNumber::~ButtonNumber()
{

}

void ButtonNumber::setData(const QVariant& data)
{
	m_data = data;
	if (data.canConvert(QVariant::Int))
	{
		setText(QString::number(data.toInt()));
	}
	if (data.canConvert(QVariant::String))
	{
		setText(data.toString());
	}
}


void ButtonNumber::setRole(const PageNavigation::Display& role)
{
	m_role = role;

	QString property = "";
	if (role.testFlag(PageNavigation::PAGE_NORMAL))
	{
		property = "normal-number";
	}
	if (role.testFlag(PageNavigation::PAGE_GUIDE_LEFT))
	{
		property = "guide-left";
	}
	if (role.testFlag(PageNavigation::PAGE_GUIDE_RIGHT))
	{
		property = "guide-right";
	}
	if (role.testFlag(PageNavigation::SELECT_NUMBER))
	{
		property = "select-number";
	}

	setProperty("type", property);

	style()->unpolish(this);
	style()->polish(this);
}