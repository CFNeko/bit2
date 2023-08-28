#include "globalapplication.h"
#include <QKeyEvent>
#include <QTranslator>
#include <QDebug>

GlobalApplication::GlobalApplication(int &argc, char **argv) : QApplication(argc, argv)
{
	initPage();
}

GlobalApplication::~GlobalApplication()
{
	m_pWidget = Q_NULLPTR;
	m_pThread->requestInterruption();
	m_pThread->quit();
	m_pThread->wait();
}

void GlobalApplication::initPage()
{
    int nTimer = 5;
	m_pThread = new QThread();
    m_pTimer = new QTimer();
	m_pTimer->moveToThread(m_pThread);
	connect(m_pThread, SIGNAL(started()), m_pTimer, SLOT(start()));
	connect(m_pTimer, &QTimer::timeout, this, &GlobalApplication::slot_timeOut);
	m_pTimer->setInterval(nTimer * 60000);
    m_pThread->start();
}

void GlobalApplication::slot_timeOut()
{
    if (!m_pWidget || !m_pWidget->isVisible() || m_pWidget->isLocked())
	{
		return;
	}
	m_pWidget->lockScreen();
}

bool GlobalApplication::notify(QObject* obj, QEvent* e)
{
	if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::KeyPress)
	{
		m_pThread->quit();
	}
	else if (e->type() == QEvent::MouseButtonRelease || e->type() == QEvent::KeyRelease)
	{
		m_pThread->start();
	}
	if (e->type() == QEvent::KeyPress)
	{
		auto*keyEvent = dynamic_cast<QKeyEvent*>(e);
		if (keyEvent == Q_NULLPTR)
		{
			return QApplication::notify(obj, e);
		}
		if (keyEvent->key() == Qt::Key_Apostrophe ||	// 全局禁用引号，防止数据库插入失败
			keyEvent->key() == Qt::Key_QuoteDbl ||
			keyEvent->key() == Qt::Key_Shift ||
			keyEvent->key() == Qt::Key_Backtab)
		{
			return true;
		}
	}
    return QApplication::notify(obj, e);
}

void GlobalApplication::setWindowInstance(MainWindow *wnd)
{
	m_pWidget = wnd;
}

MainWindow* GlobalApplication::getMainWindow()
{
    return m_pWidget;
}

bool GlobalApplication::switchApplicationLanguage(LanguageType type)
{
    if(Q_NULLPTR != m_pTranslator)
    {
        qApp->removeTranslator(m_pTranslator);
        delete m_pTranslator;
    }

    m_pTranslator = new QTranslator;

    const auto SIMPLE_CN(":/transfile/trans_smiple_cn.qm");
    const auto ENGLISH(":/transfile/trans_english.qm");
    bool flag = false;
    switch (type) {
    case LanguageType::LANGUAGE_ENGLISH:
    {
       flag = m_pTranslator->load(ENGLISH);
        break;
    }
    case LanguageType::LANGUAGE_SIMPLE_CN:
    {
        flag = m_pTranslator->load(SIMPLE_CN);
        break;
    }
    default:
        break;
    }

    if(!flag)
    {
        return false;
    }

    qApp->installTranslator(m_pTranslator);

    return true;
}
