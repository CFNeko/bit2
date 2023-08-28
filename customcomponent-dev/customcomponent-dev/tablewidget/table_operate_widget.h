#ifndef TABLE_OPERATE_WIDGET_H
#define TABLE_OPERATE_WIDGET_H

#include <QWidget>
#include <QVariantList>

namespace Ui {
	class TabelOperateWidget;
}
class TabelOperateWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TabelOperateWidget(QWidget *parent = nullptr);
	~TabelOperateWidget();

	void initBtnOperate(const QVariant& operate, const QVariant& data);
	void initBtnOperate(const QVariantList& operates, const QVariant& data);
	void updateOperate(const QVariant& data);

	auto setData(const QVariant& data) -> void
	{
		m_data.clear();
		m_data = data;
	}

	auto data() const -> QVariant
	{
		return m_data;
	}

signals:
	void signal_operate(const QVariant& operate, const QVariant& data);

private:
	Ui::TabelOperateWidget* ui;

	QVariant m_data{ QVariant() };
};

#endif //TABLE_OPERATE_WIDGET_H