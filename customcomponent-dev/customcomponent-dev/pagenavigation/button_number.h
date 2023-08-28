#ifndef BUTTON_NUMBER_H
#define BUTTON_NUMBER_H

#include "page_navigation_defines.h"
#include <QPushButton>
#include <QMouseEvent>

class ButtonNumber : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(int id READ id WRITE setId DESIGNABLE true)
	Q_PROPERTY(QVariant data READ data WRITE setData DESIGNABLE true)


public:
	//using 关键字是在C++11之后出现的，有些版本是不支持的，所以这边我们不使用
	//using QPushButton::QPushButton;

	explicit ButtonNumber(QWidget *parent = 0);
	explicit ButtonNumber(int id, QWidget *parent = 0);
	~ButtonNumber();

	int id() const
	{
		return m_id;
	}

	void setId(int id)
	{
		m_id = id;
	}

	QVariant data() const
	{
		return m_data;
	}
	void setData(const QVariant& data);

	PageNavigation::Display role() const
	{
		return m_role;
	}

	void setRole(const PageNavigation::Display& role);

	PageNavigation::NumberType type() const
	{
		return m_type;
	}

	void setType(const PageNavigation::NumberType& type)
	{
		m_type = type;
	}

private:

	int m_id{ -1 };
	QVariant m_data{ QVariant() };
	PageNavigation::Display m_role{ PageNavigation::INVAILD };
	PageNavigation::NumberType m_type{ PageNavigation::NORMAL_NUMBER };
};

#endif // BUTTON_NUMBER_H
