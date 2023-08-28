#include "table_operate_widget.h"
#include "ui_table_operate_widget.h"
#include "table_defines.h"
#include "operate_button.h"

TabelOperateWidget::TabelOperateWidget(QWidget *parent) :QWidget(parent), ui(new Ui::TabelOperateWidget)
{
	ui->setupUi(this);

#if SUPPORT_C11
#else
    UserOperate::MapInsert::initOperate();
#endif
}

TabelOperateWidget::~TabelOperateWidget()
{
	delete ui;
}

void TabelOperateWidget::initBtnOperate(const QVariant& operate, const QVariant& data)
{
	auto* btn = new OperateButton(UserOperate::instance()[operate.toInt()]);
	btn->setData(operate);
	connect(btn, &QPushButton::clicked, this, [this]() {
		auto* btn = qobject_cast<OperateButton*>(sender());
		if (Q_NULLPTR == btn)
		{
			return;
		}
		emit signal_operate(btn->data(), this->data());
	});

	ui->horiOPerate->addWidget(btn);

	setData(data);
}

void TabelOperateWidget::initBtnOperate(const QVariantList& operates, const QVariant& data)
{
	for (const auto& text : operates)
	{
		auto* btn = new OperateButton(UserOperate::instance()[text.toInt()]);
		btn->setData(text);
		connect(btn, &QPushButton::clicked, this, [this]() {
			auto* btn = qobject_cast<OperateButton*>(sender());
			if (Q_NULLPTR == btn)
			{
				return;
			}
			emit signal_operate(btn->data(), this->data());
		});

		ui->horiOPerate->addWidget(btn);
	}

	setData(data);
}

void TabelOperateWidget::updateOperate(const QVariant& data)
{
	/*for (int index = 0, size = ui->horiOPerate->count(); index < size; ++index)
	{
		auto* btn = static_cast<OperateButton*>(ui->horiOPerate->itemAt(index)->widget());
		if (btn == Q_NULLPTR)
		{
			continue;
		}
	}*/

	//数据保存在这一步，因此无需更新更下层的数据
}
