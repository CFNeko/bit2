#include "table_head_cell_widget.h"
#include "ui_table_head_cell_widget.h"

TableHeadCellWidget::TableHeadCellWidget(QWidget *parent) :QWidget(parent), ui(new Ui::TableHeadCellWidget)
{
	ui->setupUi(this);
	initPage();
}

TableHeadCellWidget::~TableHeadCellWidget()
{
	delete ui;
}

void TableHeadCellWidget::initPage()
{
	connect(ui->btnAsc, &QPushButton::clicked, this, [this]()
	{
		emit signal_sort(Table::ASCENDING, data());
	});

	connect(ui->btnDesc, &QPushButton::clicked, this, [this]()
	{
		emit signal_sort(Table::DESCENDING, data());
	});
}

void TableHeadCellWidget::setText(const QString& text)
{
	ui->lbText->setText(text);
}

auto TableHeadCellWidget::text() const -> QString
{
	return ui->lbText->text();
}

void TableHeadCellWidget::setSortVisible(bool visible)
{
	ui->btnAsc->setVisible(visible);
	ui->btnDesc->setVisible(visible);
}