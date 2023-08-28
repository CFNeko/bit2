#ifndef OPERATE_BUTTON_H
#define OPERATE_BUTTON_H

#include <QPushButton>
#include <QVariant>

class OperateButton : public QPushButton
{
	Q_OBJECT

public:
	explicit OperateButton(QString text, QWidget* parent = nullptr);

	~OperateButton();

	void setData(const QVariant& data)
	{
		m_data = data;
	}

	QVariant data() const
	{
		return m_data;
	}
protected:

	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);

private:
	QVariant m_data{ QVariant() };
};

#endif //OPERATE_BUTTON_H