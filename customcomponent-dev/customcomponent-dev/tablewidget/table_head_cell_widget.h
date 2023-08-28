#ifndef TABLE_HEAD_CELL_WIDGET_H
#define TABLE_HEAD_CELL_WIDGET_H

#include "table_defines.h"
#include <QWidget>
#include <QVariantList>

namespace Ui {
	class TableHeadCellWidget;
}
class TableHeadCellWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TableHeadCellWidget(QWidget *parent = nullptr);
	~TableHeadCellWidget();


	auto setData(const QVariant& data) -> void
	{
		m_data = data;
	}

	auto data() const -> QVariant
	{
		return m_data;
	}

	void setText(const QString& text);
	
	auto text() const -> QString;

	void setSortVisible(bool visible = false);

private:
	void initPage();

signals:
	void signal_sort(const Table::TableSort& mode, const QVariant& data);
private:
	Ui::TableHeadCellWidget* ui;

	QVariant m_data{ QVariant() };
};

#endif //TABLE_HEAD_CELL_WIDGET_H