#include "mask_widget.h"
#include "ui_mask_widget.h"
#include "globalapplication.h"
#include <QDebug>

MaskWidget * MaskWidget::m_pSelf = Q_NULLPTR;

MaskWidget * MaskWidget::Instance()
{
	if (m_pSelf == Q_NULLPTR)
	{
		m_pSelf = new MaskWidget;
	}
	return m_pSelf;
}

MaskWidget::MaskWidget(QWidget *parent) : QDialog(parent), ui(new Ui::MaskWidget)
{
	ui->setupUi(this);
	hide();
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |  Qt::WindowDoesNotAcceptFocus);     //Qt:: |
    qApp->installEventFilter(this);
}

MaskWidget::~MaskWidget()
{
	delete ui;
}

void MaskWidget::setMainWidget(QWidget *pWidget)
{
	this->setFixedSize(QSize(pWidget->width(), pWidget->height()));
	this->setParent(pWidget);
	this->move(pWidget->x(), pWidget->y());
}

void MaskWidget::setDialogNames(const QStringList &dialogNames)
{
    if (this->m_dialogNames != dialogNames)
    {
        this->m_dialogNames = dialogNames;
    }
}

bool MaskWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Show) 
	{
        if (!m_dialogNames.contains(obj->objectName()))
		{
			return QObject::eventFilter(obj, event);
        }
		this->show();
		auto pWidget = dynamic_cast<QWidget*>(obj);
		if (Q_NULLPTR == pWidget)
		{
			return QObject::eventFilter(obj, event);
		}
		pWidget->activateWindow();
		pWidget->setFocus(Qt::ActiveWindowFocusReason);
		this->stackUnder(pWidget);

		auto mainWidget = app->getMainWindow();
		if (Q_NULLPTR == mainWidget)
		{
			return QObject::eventFilter(obj, event);
		}
		mainWidget->stackUnder(this);
		QRect screenGeometry = mainWidget->geometry();
		int x = screenGeometry.x() + (screenGeometry.width() - pWidget->width()) / 2;
		int y = screenGeometry.y() + (screenGeometry.height() - pWidget->height()) / 2;

		pWidget->move(x, y);
    } 
	else if (event->type() == QEvent::Hide)
	{
        if (m_dialogNames.contains(obj->objectName()))
		{
            hide();
        }
    }

    return QObject::eventFilter(obj, event);
}
