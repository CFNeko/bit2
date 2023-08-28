#ifndef SEARCH_LINE_H
#define SEARCH_LINE_H

#include <QLineEdit>
#include <QVariant>

class SearchLine : public QLineEdit
{
	Q_OBJECT

public:
	explicit SearchLine(QWidget* parent = nullptr);

	~SearchLine();

	void setData(const QVariant& data)
	{
		m_data = data;
	}

	QVariant data() const
	{
		return m_data;
	}

private:
	void initPage();

private:
	QVariant m_data{ QVariant() };
};

#endif //SEARCH_LINE_H