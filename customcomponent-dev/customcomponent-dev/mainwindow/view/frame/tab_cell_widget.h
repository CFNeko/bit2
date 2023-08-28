#ifndef TAB_CELL_TEMPLATE_H
#define TAB_CELL_TEMPLATE_H

#include <QWidget>
#include <QMap>

class BaseWidget;

namespace Ui {
	class TabCellWidget;
}

class TabCellWidget : public QWidget
{
	Q_OBJECT

public:
	TabCellWidget(QWidget *parent = Q_NULLPTR);
	~TabCellWidget();

private:
	void initPage();
    template<typename T>bool addTab(const QString& page, int id, T&pWidget);
    void addWidgetByPage(const QString& page, int id);

public slots :
    void slot_subMenuClicked(const QString&page, int id);
    void slot_nextsubMenuClicked(const QString& page, int id, bool& change);

private:
	Ui::TabCellWidget *ui;
    QMap<int, int>	m_mapSubPage;
    QMap<int, BaseWidget*> m_mapSubPageWidget;
    int m_nCurrentIndex{ -1 };  //当前的页签
};
#endif // TAB_CELL_TEMPLATE_H
