#include "page_navigation_widget.h"
#include "ui_page_navigation_widget.h"
#include "button_number.h"

PageNavigationWidget::PageNavigationWidget(QWidget *parent) : QWidget(parent), ui(new Ui::PageNavigationWidget)
{
	ui->setupUi(this);
	initPage();
}

PageNavigationWidget::~PageNavigationWidget()
{
	delete ui;
}

void PageNavigationWidget::initPage()
{
	for (int index = 0; index < PageNavigation::BUTTON_NUMBER; ++index)
	{
		auto* btn = new ButtonNumber;
		btn->setFixedSize(QSize(30, 30));
		
		ui->horiPage->addWidget(btn);
		m_btn.append(QVariant::fromValue(static_cast<void*>(btn)));

		connect(btn, &QPushButton::clicked, this, [this]
		{
			for (const auto& pbt : m_btn)
			{
				auto* pb = static_cast<ButtonNumber*>(pbt.value<void*>());
				if (Q_NULLPTR == pb)
				{
					continue;
				}

				if (pb->role().testFlag(PageNavigation::SELECT_NUMBER))
				{
					pb->setRole(PageNavigation::PAGE_NORMAL);
					break;
				}
			}
			auto* const btn = qobject_cast<ButtonNumber*>(sender());
			btn->setRole(PageNavigation::SELECT_NUMBER);

			if (btn->type() == PageNavigation::NORMAL_NUMBER)
			{
				m_current = btn->data().toInt();
			}
			else if (btn->type() == PageNavigation::GUIDE_LEFT_NUMBER)
			{
				m_current = m_current - 5 > 0 ? m_current - 5 : 1;
			}
			else if (btn->type() == PageNavigation::GUIDE_RIGHT_NUMBER)
			{
				m_current = m_current + 5 > total() ? total() : m_current + 5;
			}

			emit signal_page(m_current);
			updateUi();
		});
	}

	connect(ui->btnPrev, &QPushButton::clicked, this, [this]()
	{
		if (m_current == 1)
		{
			return;
		}

		m_current -= 1;
		emit signal_page(m_current);
		update();
	});

	connect(ui->btnNext, &QPushButton::clicked, this, [this]()
	{
		if (m_current == total())
		{
			return;
		}

		m_current += 1;
		emit signal_page(m_current);
		updateUi();
	});

	connect(ui->spinPage, &QSpinBox::editingFinished, this, [this] ()
	{
		int val = ui->spinPage->value();
		m_current = val > total() ? total() : val;
		emit signal_page(m_current);
		updateUi();
	});
}

void PageNavigationWidget::setTotal(int total)
{
	m_total = total % PageNavigation::CURRENT_PAGE_NUMBER ? total / PageNavigation::CURRENT_PAGE_NUMBER + 1 : total / PageNavigation::CURRENT_PAGE_NUMBER;
	
	m_current = m_current == 0 ? 1 : m_current;
	m_current = m_total < m_current ? m_total : m_current;

	ui->lbTotal->setText(QString::fromLocal8Bit("¹² %1 Ò³ %2 ÐÐ.").arg(m_total).arg(total));

	updateUi();
}

void PageNavigationWidget::updateUi()
{
	for (const auto& button : m_btn)
	{
		auto btn = static_cast<ButtonNumber*>(button.value<void*>());
		if (Q_NULLPTR == btn)
		{
			continue;
		}

		btn->setRole(PageNavigation::PAGE_NORMAL);

		btn->setVisible(true);
	}

	if (total() < PageNavigation::BUTTON_NUMBER)
	{
		for (int index = 0; index < m_btn.size(); ++index)
		{
			auto btn = static_cast<ButtonNumber*>(m_btn[index].value<void*>());
			if (Q_NULLPTR == btn)
			{
				continue;
			}

			btn->setData(index + 1);
			btn->setType(PageNavigation::NORMAL_NUMBER);
			btn->setRole(m_current == btn->data().toInt() ? PageNavigation::SELECT_NUMBER : PageNavigation::PAGE_NORMAL);

			if (index < total())
			{
				continue;
			}
			btn->setVisible(false);
		}
	}
	else if (m_current < 7)
	{
		for (int index = 0; index < 7; ++index)
		{
			auto btn = static_cast<ButtonNumber*>(m_btn[index].value<void*>());
			if (Q_NULLPTR == btn)
			{
				continue;
			}

			btn->setData(index + 1);
			btn->setType(PageNavigation::NORMAL_NUMBER);
			btn->setRole(m_current == btn->data().toInt() ? PageNavigation::SELECT_NUMBER : PageNavigation::PAGE_NORMAL);
		}

		auto btn = static_cast<ButtonNumber*>(m_btn[7].value<void*>());
		btn->setData("");
		btn->setType(PageNavigation::GUIDE_RIGHT_NUMBER);
		btn->setRole(PageNavigation::PAGE_GUIDE_RIGHT);

		btn = static_cast<ButtonNumber*>(m_btn[8].value<void*>());
		btn->setData(total());
		btn->setType(PageNavigation::NORMAL_NUMBER);
		btn->setRole(PageNavigation::PAGE_NORMAL);
	}
	else if (m_current + 6 > total())
	{
		for (int index = 2; index < 9; ++index)
		{
			auto btn = static_cast<ButtonNumber*>(m_btn[index].value<void*>());
			if (Q_NULLPTR == btn)
			{
				continue;
			}

			btn->setData(total() - 8 + index);
			btn->setType(PageNavigation::NORMAL_NUMBER);
			btn->setRole(m_current == btn->data().toInt() ? PageNavigation::SELECT_NUMBER : PageNavigation::PAGE_NORMAL);
		}

		auto btn = static_cast<ButtonNumber*>(m_btn[1].value<void*>());
		btn->setData("");
		btn->setType(PageNavigation::GUIDE_LEFT_NUMBER);
		btn->setRole(PageNavigation::PAGE_GUIDE_LEFT);

		btn = static_cast<ButtonNumber*>(m_btn[0].value<void*>());
		btn->setData(1);
		btn->setType(PageNavigation::NORMAL_NUMBER);
		btn->setRole(PageNavigation::PAGE_NORMAL);
	}
	else
	{
		for (int index = 2; index < 7; ++index)
		{
			auto btn = static_cast<ButtonNumber*>(m_btn[index].value<void*>());
			if (Q_NULLPTR == btn)
			{
				continue;
			}

			btn->setData(m_current + index - 4);
			btn->setType(PageNavigation::NORMAL_NUMBER);
			btn->setRole(m_current == btn->data().toInt() ? PageNavigation::SELECT_NUMBER : PageNavigation::PAGE_NORMAL);
		}

		auto btn = static_cast<ButtonNumber*>(m_btn[1].value<void*>());
		btn->setData("");
		btn->setType(PageNavigation::GUIDE_LEFT_NUMBER);
		btn->setRole(PageNavigation::PAGE_GUIDE_LEFT);

		btn = static_cast<ButtonNumber*>(m_btn[0].value<void*>());
		btn->setData(1);
		btn->setType(PageNavigation::NORMAL_NUMBER);
		btn->setRole(PageNavigation::PAGE_NORMAL);

		btn = static_cast<ButtonNumber*>(m_btn[7].value<void*>());
		btn->setData("");
		btn->setType(PageNavigation::GUIDE_RIGHT_NUMBER);
		btn->setRole(PageNavigation::PAGE_GUIDE_RIGHT);

		btn = static_cast<ButtonNumber*>(m_btn[8].value<void*>());
		btn->setData(total());
		btn->setType(PageNavigation::NORMAL_NUMBER);
		btn->setRole(PageNavigation::PAGE_NORMAL);
	}
}