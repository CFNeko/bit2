#ifndef PAGE_NAVIGATION_WIDGET_H
#define PAGE_NAVIGATION_WIDGET_H

#include <QWidget>
#include <QVariant>
namespace Ui {
class PageNavigationWidget;
}

class QButtonGroup;

class PageNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageNavigationWidget(QWidget *parent = nullptr);
    ~PageNavigationWidget();

	void setTotal(int total);

	int total() const
	{
		return m_total;
	}

	int current() const
	{
		return m_current;
	}

	PageNavigationWidget(const PageNavigationWidget& other) = delete;
	PageNavigationWidget& operator=(const PageNavigationWidget& other) = delete;
	
private:
    void initPage();
	void updateUi();

signals:
	void signal_page(int index);

private:
    Ui::PageNavigationWidget *ui;
    QList<QVariant> m_btn;
    //QList<QVariant> m_btn{};  //低版本编译器会报编译器内部错误

	int m_total{ 0 };
	int m_current{ 0 };
};

#endif // PAGE_NAVIGATION_WIDGET_H
