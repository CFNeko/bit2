#include "check_box.h"
#include "table_widget.h"
#include "ui_table_widget.h"
#include "table_operate_widget.h"
#include "table_head_cell_widget.h"
#include "page_navigation_defines.h"
#include <QToolTip>
#include <QPushButton>
#include <QButtonGroup>

TableWidget::TableWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TableWidget)
{
    ui->setupUi(this);
    initPage();
}

TableWidget::~TableWidget()
{
    delete ui;
	m_btnGroup->deleteLater();
}

void TableWidget::initPage()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    ui->tbBody->setMouseTracking(true);

    connect(ui->tbBody, &QTableWidget::cellPressed, this, [this](int r, int c) {
	    auto* item = ui->tbBody->item(r, c);
        if (Q_NULLPTR == item)
        {
            return;
        }
        QToolTip::showText(QCursor::pos(), item->text());
    });

	connect(ui->tbBody, &QTableWidget::doubleClicked, this, [this] {

		QList<QTableWidgetItem*> items = ui->tbBody->selectedItems();
		if (items.isEmpty())
		{ 
			return;
		}

		int row = ui->tbBody->row(items.at(0));
		QVariantList body;

		if (m_check)
		{
			body = static_cast<QWidget*>(ui->tbBody->cellWidget(row, 0))->findChild<CheckBox*>()->data().toList();
		}
		else
		{
			body = ui->tbBody->item(row, 0)->data(Qt::UserRole).toList();
		}

		emit signal_rowData(body);
	});

	connect(ui->wdgPage, &PageNavigationWidget::signal_page, this, [this](int index) 
	{
		updateTableData(m_searchedDt);
	});

	setEditTriggerMode(QAbstractItemView::NoEditTriggers);

	m_btnGroup = new QButtonGroup(this);
	m_btnGroup->setExclusive(true);
}

void TableWidget::setEditTriggerMode(const QAbstractItemView::EditTriggers& mode) const
{
	ui->tbBody->setEditTriggers(mode);
	ui->tbHeader->setEditTriggers(mode);
}

void TableWidget::initTableHeader(const QStringList& header, bool check)
{
    ui->tbHeader->setColumnCount(check ? (header.size() + 1) : header.size());
    ui->tbBody->setColumnCount(check ? (header.size() + 1) : header.size());

	m_check = check;

	int index = 0;
	if (check)
	{
		auto* pWidget = newBtnCheckBox("", true);
		ui->tbHeader->setCellWidget(0, index, pWidget);
	}
	
	for (const auto& text : header)
	{
		auto* pWidget = new TableHeadCellWidget(this);
		pWidget->setMinimumHeight(40);
		pWidget->setText(text);
		pWidget->setData(++index);
		ui->tbHeader->setCellWidget(0, index, pWidget);

		connect(pWidget, &TableHeadCellWidget::signal_sort, this, [this](const Table::TableSort& mode, const QVariant& data)
		{
			ui->tbBody->sortByColumn(data.toInt(), static_cast<Qt::SortOrder>(static_cast<int>(mode)));
		});

		auto btnList = pWidget->findChildren<QPushButton*>();

		for (const auto& btn : btnList)
		{
			m_btnGroup->addButton(btn, m_btnGroup->buttons().size());
		}
	}
}

void TableWidget::initTableSortColumn(const QList<int>& sort) const
{
	int count = m_check ? ui->tbHeader->columnCount() - 1 : ui->tbHeader->columnCount();
	if (sort.size() != count)
	{
		return;
	}

	for (auto index = 0, size = sort.size(); index < size; ++index)
	{
		auto* pWidget = dynamic_cast<TableHeadCellWidget*>(ui->tbHeader->cellWidget(0, m_check ? (index + 1) : index));
		
		if (Q_NULLPTR == pWidget)
		{
			continue;
		}
		pWidget->setSortVisible(sort[index]);
	}
}

void TableWidget::initTableColumnWidth(const QList<int>& width) const
{
	int count = m_check ? ui->tbHeader->columnCount() - 1 : ui->tbHeader->columnCount();
	if (width.size() != count)
	{
		return;
	}

	QList<int> wth(width);

	if(m_check)
	{
		wth.push_front(40);
	}

    for (auto index = 0; index < wth.size(); ++index)
    {
        ui->tbHeader->setColumnWidth(index, wth[index]);
        ui->tbBody->setColumnWidth(index, wth[index]);
    }
}

void TableWidget::setTableData(const QList<QVariantList>& data)
{
	m_data = data;
    updateTableData(data);
}

void TableWidget::setTableCellData(int r, int c, const QVariant& value) const
{
    ui->tbBody->item(r, c)->setText(value.toString());
}

void TableWidget::setTableColumnData(int c, const QVariant& value) const
{
    for (int index = 0, nRet = ui->tbBody->rowCount(); index < nRet; ++index)
    {
        ui->tbBody->item(index, c)->setText(value.toString());
    }
}

void TableWidget::searchRowByField(const QVariant& field, const QVariant& target)
{
	if (target.isNull() || target.toString().isEmpty())
	{
		m_searchedDt.clear();
		updateTableData(m_searchedDt);
		return;
	}

	auto index = 0;
	for (auto size = ui->tbHeader->columnCount(); index < size; ++index)
	{
		auto* pWidget = dynamic_cast<TableHeadCellWidget*>(ui->tbHeader->cellWidget(0, m_check ? (index + 1) : index));

		if (Q_NULLPTR == pWidget)
		{
			continue;
		}
		if (pWidget->text() == field.toString())
		{
			break;
		}
	}

	QList<QVariantList> data;

	for (const auto& row : m_data)
	{
		if (row[index].toString().contains(target.toString()))
		{
			data.append(row);
		}
	}

	m_searchedDt = data;
	updateTableData(data);	
}

void TableWidget::deleteRow()
{
	for (int index = 0, size = ui->tbBody->rowCount(); index < size; ++index)
	{
		QVariant dt;
		auto btn = static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0))->findChild<CheckBox*>();
		if (Q_NULLPTR == btn || !btn->isChecked())
		{
			continue;
		}

		dt = m_check ? btn->data() : ui->tbBody->item(index, 0)->data(Qt::UserRole);

		m_data.removeOne(dt.toList());
		m_searchedDt.removeOne(dt.toList());
	}

	updateTableData(m_searchedDt);
}

void TableWidget::deleteRow(const QVariant& data)
{
	m_data.removeOne(data.toList());
	m_searchedDt.removeOne(data.toList());

	updateTableData(m_searchedDt);
}

void TableWidget::setTableCellOperate(int r, int c, const QVariant& operate, const QVariant& data)
{
	auto* pWidget = new TabelOperateWidget(this);
	
	ui->tbBody->setCellWidget(r, c, pWidget);

	QVariant dt(data);
	if (data.isNull())
	{
		if (m_check)
		{
			dt = static_cast<QWidget*>(ui->tbBody->cellWidget(r, 0))->findChild<CheckBox*>()->data();
		}
		else
		{
			dt = ui->tbBody->item(r, 0)->data(Qt::UserRole);
		}
	}

	pWidget->initBtnOperate(operate, dt);

	connect(pWidget, &TabelOperateWidget::signal_operate, this, &TableWidget::signal_operate);

	UserOperate::UserOperater op;
	op.row = r;
	op.column = c;
	op.type = 1;
	op.operate = operate;
	m_operates.append(op);
}

void TableWidget::setTableColumnOperate(int c, const QVariantList& operates, const QVariant& data)
{
	if (operates.size() < ui->tbBody->rowCount())
	{
		return; //格式不对，会越界
	}
	for (auto index = 0, nRet = ui->tbBody->rowCount(); index < nRet; ++index)
	{
		auto pWidget = new TabelOperateWidget(this);
		
		ui->tbBody->setCellWidget(index, c, pWidget);

		QVariant dt(data);
		if (data.isNull())
		{
			if (m_check)
			{
				dt = static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0))->findChild<CheckBox*>()->data();
			}
			else
			{
				dt = ui->tbBody->item(index, 0)->data(Qt::UserRole);
			}
		}
		pWidget->initBtnOperate(operates[index], dt);

		connect(pWidget, &TabelOperateWidget::signal_operate, this, &TableWidget::signal_operate);
	}

	UserOperate::UserOperater op;
	op.column = c;
	op.type = 0;
	op.operate = operates;
	m_operates.append(op);
} 

void TableWidget::setTableColumnOperates(int c, const QVariantList& operates, const QVariant& data)
{
	for (int index = 0, nRet = ui->tbBody->rowCount(); index < nRet; ++index)
	{
		auto* pWidget = new TabelOperateWidget(this);
		ui->tbBody->setCellWidget(index, c, pWidget);

		QVariant dt(data);
		if (data.isNull())
		{
			if (m_check)
			{
				dt = static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0))->findChild<CheckBox*>()->data();
			}
			else
			{
				dt = ui->tbBody->item(index, 0)->data(Qt::UserRole);
			}
		}
		pWidget->initBtnOperate(operates, dt);

		connect(pWidget, &TabelOperateWidget::signal_operate, this, &TableWidget::signal_operate);
	}

	UserOperate::UserOperater op;
	op.column = c;
	op.type = 1;
	op.operate = operates;
	m_operates.append(op);
}

void TableWidget::data(QList<QVariantList>& data, bool header, bool number) const
{
    if (header)
    {
		QVariantList head;
        if (number)
        {
            head.append("index");
        }
        for (int index = 1, column = ui->tbHeader->columnCount(); index < column; ++index)
        {
            head.append(ui->tbHeader->item(0, index)->text());
        }

        data << head;
    }

	for (int index = 0, size = ui->tbBody->rowCount(); index < size; ++index)
	{
		auto* pWidget = static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0));
		auto* pBtn = pWidget->findChild<QCheckBox*>(QString("btnCheck"));
		if (Q_NULLPTR == pBtn || !pBtn->isChecked())
		{
			continue;
		}

		QVariantList body;

		if (number)
		{
			body.append(QString::number(index + 1));
		}

		auto nRet = 0;
		if (m_check)
		{
			++nRet;
		}

		for (const auto column = ui->tbHeader->columnCount(); nRet < column; ++nRet)
		{
			body.append(ui->tbBody->item(index, nRet)->data(Qt::UserRole));
		}

		data.append(body);
	}
}

void TableWidget::initTableData(const QList<QVariantList>& data)
{
	auto btn = static_cast<QWidget*>(ui->tbHeader->cellWidget(0, 0))->findChild<QCheckBox*>(QString("btnCheck"));
	if (btn != Q_NULLPTR && btn->checkState() != Qt::Checked)
	{
		btn->setChecked(false);
	}
	ui->tbBody->setRowCount(data.size());
	ui->tbBody->setUpdatesEnabled(false);

	for (int index = 0, size = data.size(); index < size; ++index)
	{
		auto ret = 0;
		if (m_check)
		{
			auto* pWidget = newBtnCheckBox("");
			ui->tbBody->setCellWidget(index, ret++, pWidget);
		}

		QVariantList list = data.at(index);

		for (const auto& text : list)
		{
			ui->tbBody->setItem(index, ret, new QTableWidgetItem());
			ui->tbBody->item(index, ret)->setData(Qt::DisplayRole, text);
			ui->tbBody->item(index, ret)->setData(Qt::UserRole, text);
			ui->tbBody->item(index, ret++)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		if (m_check)
		{
			static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0))->findChild<CheckBox*>()->setData(list);
		}
		else
		{
			ui->tbBody->item(index, 0)->setData(Qt::UserRole, list);
		}
	}

	ui->tbBody->setUpdatesEnabled(true);
}

QWidget* TableWidget::newBtnCheckBox(const QString& strText, bool header) const
{
	auto* pBtnCheck = new CheckBox(strText);
    pBtnCheck->setObjectName(QString("btnCheck"));
    pBtnCheck->setFixedSize(40, 36);

    pBtnCheck->setProperty("buttontext", "field");

	auto* pWidget = new QWidget;
	auto* layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(pBtnCheck);
    pWidget->setLayout(layout);
    
	auto* pWidgetAll = static_cast<QWidget*>(ui->tbHeader->cellWidget(0, 0));
	auto* pBtnAll = pWidgetAll->findChild<QCheckBox*>(QString("btnCheck"));
    connect(pBtnAll, &QCheckBox::clicked, pBtnCheck, &QCheckBox::setChecked);

	if (!header)
	{
		connect(pBtnCheck, &QCheckBox::clicked, this, &TableWidget::on_btnCheckClicked);
		if (pBtnAll->checkState() == Qt::Checked)
		{
			pBtnCheck->setChecked(true);
		}
	}
	
    return pWidget;
}

void TableWidget::on_btnCheckClicked() const
{
    auto* const pWidget = static_cast<QWidget*>(ui->tbHeader->cellWidget(0, 0));
    auto* const pBtnAll = pWidget->findChild<QCheckBox*>(QString("btnCheck"));
    if (Q_NULLPTR == pBtnAll)
    {
        return;
    }

    auto* const pcurBtn = qobject_cast<QCheckBox*>(QObject::sender());
    if (Q_NULLPTR == pcurBtn)
    {
        return;
    }
    pBtnAll->setCheckState(pcurBtn->checkState());

    for (int index = 0; index < ui->tbBody->rowCount(); ++index)
    {
        auto* const widget = static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0));
        auto* const pBtn = widget->findChild<QCheckBox*>(QString("btnCheck"));
        if (Q_NULLPTR == pBtn)
        {
            continue;
        }

        if (pBtn->checkState() != pBtnAll->checkState())
        {
            pBtnAll->setCheckState(Qt::PartiallyChecked);
            break;
        }
    }
}

void TableWidget::updateTableUserOPerate()
{
	if (m_operates.isEmpty())
	{
		return;
	}

	for (const auto& op : m_operates)
	{
		if (op.row != -1)
		{
			if (op.row > ui->tbBody->rowCount())
			{
				continue;
			}

			QVariant dt;
			if (m_check)
			{
				dt = static_cast<QWidget*>(ui->tbBody->cellWidget(op.row, 0))->findChild<CheckBox*>()->data();
			}
			else
			{
				dt = ui->tbBody->item(op.row, 0)->data(Qt::UserRole);
			}

			auto* pWidget = static_cast<TabelOperateWidget*>(ui->tbBody->cellWidget(op.row, op.column));
			if (pWidget != Q_NULLPTR)
			{
				pWidget->setData(dt);
			}
			auto* pOp = new TabelOperateWidget(this);
			ui->tbBody->setCellWidget(op.row, op.column, pOp);
			pOp->initBtnOperate(op.operate, dt);
			connect(pOp, &TabelOperateWidget::signal_operate, this, &TableWidget::signal_operate);
			continue;
		}
		
		for (int index = 0, size = ui->tbBody->rowCount(); index < size; ++index)
		{
			QVariant dt;
			if (m_check)
			{
				dt = static_cast<QWidget*>(ui->tbBody->cellWidget(index, 0))->findChild<CheckBox*>()->data();
			}
			else
			{
				dt = ui->tbBody->item(index, 0)->data(Qt::UserRole);
			}

			auto* pWidget = static_cast<TabelOperateWidget*>(ui->tbBody->cellWidget(index, op.column));
			if (pWidget != Q_NULLPTR)
			{
				pWidget->setData(dt);
				continue;
			}


			auto* pOp = new TabelOperateWidget(this);
			ui->tbBody->setCellWidget(index, op.column, pOp);
			if (op.type == 1)
			{
				pOp->initBtnOperate(op.operate.toList(), dt);
			}
			else
			{
				pOp->initBtnOperate(op.operate.toList().at(index), dt);
			}

			connect(pOp, &TabelOperateWidget::signal_operate, this, &TableWidget::signal_operate);
		}
	}
}

void TableWidget::updateTableData(const QList<QVariantList>& data)
{
	QList<QVariantList> dt = data.isEmpty() ? m_data : data;
	ui->wdgPage->setTotal(dt.size());

	int start = PageNavigation::CURRENT_PAGE_NUMBER * (ui->wdgPage->current() - 1);
	if (start > dt.size())
	{
		return;
	}

	int end = PageNavigation::CURRENT_PAGE_NUMBER * ui->wdgPage->current();
	end = end > dt.size() ? dt.size() : end;

	std::list<QVariantList> tmp(dt.begin() + start, dt.begin() + end);
	QList<QVariantList> dpyData = QList<QVariantList>::fromStdList(tmp);

	initTableData(dpyData);
	updateTableUserOPerate();
}
