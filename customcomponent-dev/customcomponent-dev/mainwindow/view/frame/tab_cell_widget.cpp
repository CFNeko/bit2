#include "tab_cell_widget.h"
#include "ui_tab_cell_widget.h"
#include "base_widget.h"
#include "menu_defines.h"
#include "testwidget.h"

#include <QDebug>
using namespace menu;
TabCellWidget::TabCellWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TabCellWidget)
{
	ui->setupUi(this);
	initPage();
}

TabCellWidget::~TabCellWidget()
{
}

void TabCellWidget::initPage()
{
	for (int nIndex = 0; nIndex < ui->stackedWidget->count(); ++nIndex)
	{
		QWidget* pWidget = ui->stackedWidget->widget(nIndex);
		if (Q_NULLPTR == pWidget)
		{
			continue;
		}
		ui->stackedWidget->removeWidget(pWidget);
		pWidget->deleteLater();
	}
}

template<typename T>bool TabCellWidget::addTab(const QString& page, int id, T& pWidget)
{
	if (Q_NULLPTR == pWidget)
	{
        qDebug() << pWidget;
        return false;
	}
	ui->stackedWidget->addWidget(pWidget);
	
	int nIndex = ui->stackedWidget->count() - 1;
    m_mapSubPage.insert(id, nIndex);

    m_mapSubPageWidget.insert(id, static_cast<BaseWidget*>(pWidget));
	return true;
}

void TabCellWidget::slot_subMenuClicked(const QString &page, int id)
{
    if (!m_mapSubPage.contains(id))
    {
        addWidgetByPage(page, id);
    }
    ui->stackedWidget->setCurrentIndex(m_mapSubPage[id]);
    m_nCurrentIndex = id;
}

void TabCellWidget::slot_nextsubMenuClicked(const QString& page, int id, bool& change)
{
    if (!m_mapSubPage.contains(id))
    {
        addWidgetByPage(page, id);
    }
    auto pWidget = m_mapSubPageWidget.value(m_nCurrentIndex);
    if(Q_NULLPTR != pWidget)
    {
        change = pWidget->saveRequest();
    }
}

void TabCellWidget::addWidgetByPage(const QString& page, int id)
{
	if (page.isEmpty())
	{
		return;
	}

    else if (MenuDefines::instance().SUB_MENU_STATION == page)
    {
        auto pWidget = new TestWidget(this);
        addTab(MenuDefines::instance().SUB_MENU_STATION, id, pWidget);
    }
    else if (MenuDefines::instance().SUB_MENU_SYSTEM == page)
    {
        auto pWidget = new TestWidget(this);
        addTab(MenuDefines::instance().SUB_MENU_SYSTEM, id, pWidget);
    }
}
