#ifndef MASKWIDGET_H
#define MASKWIDGET_H

#include <QDialog>
#include <QMutex>

namespace Ui {
	class MaskWidget;
}
class MaskWidget : public QDialog
{
    Q_OBJECT
public:
	static MaskWidget *Instance();
	void setMainWidget(QWidget *mainWidget);
	void setDialogNames(const QStringList &dialogNames);
protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
	explicit MaskWidget(QWidget *parent = 0);
	~MaskWidget();
private:
	Ui::MaskWidget* ui;
    QStringList m_dialogNames;    //可能弹窗的窗体对象名称集合链表

	static MaskWidget* m_pSelf;


};

#endif // MASKWIDGET_H
