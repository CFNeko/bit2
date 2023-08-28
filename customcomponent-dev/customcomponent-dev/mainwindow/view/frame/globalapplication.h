#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H

#include "mainwindow.h"
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QApplication>

class GlobalApplication;
#define app dynamic_cast<GlobalApplication*>(QApplication::instance())

class GlobalApplication : public QApplication
{
	Q_OBJECT
public:
    enum LanguageType{
        LANGUAGE_SIMPLE_CN = 0,
        LANGUAGE_ENGLISH
    };

	GlobalApplication(int &argc, char **argv);
	~GlobalApplication();

    MainWindow* getMainWindow();


	bool notify(QObject* obj, QEvent* event) override;
    void setWindowInstance(MainWindow* wnd);

    bool switchApplicationLanguage(LanguageType type);

private:
	void initPage();

private slots:
	void slot_timeOut();

signals:


private:
    MainWindow*		m_pWidget{ Q_NULLPTR };
    QTimer*			m_pTimer{ Q_NULLPTR }; //定时器
    QThread*		m_pThread{ Q_NULLPTR }; //定时器线程
    QTranslator*    m_pTranslator{ Q_NULLPTR };

};

#endif // GLOBALAPPLICATION_H
