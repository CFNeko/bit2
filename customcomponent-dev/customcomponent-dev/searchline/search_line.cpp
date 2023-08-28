#include "search_line.h"
#include <QPushButton>
#include <QHBoxLayout>

SearchLine::SearchLine(QWidget *parent) : QLineEdit(parent)
{
	initPage();
}

SearchLine::~SearchLine()
{

}

void SearchLine::initPage()
{
	this->setProperty("type", "search");
	
	auto* btn = new QPushButton(this);
	auto* layout = new QHBoxLayout(this);
	layout->addStretch();
	layout->addWidget(btn);
	layout->setContentsMargins(0, 5, 0, 0);
	this->setLayout(layout);
	btn->setProperty("type", "search");
	connect(btn, &QPushButton::clicked, this, [this]()
	{
		emit textEdited(this->text());
	});
}
