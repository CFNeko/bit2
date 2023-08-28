#ifndef MENU_BAR_WIDGET_H
#define MENU_BAR_WIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QButtonGroup>
#include <QPushButton>

namespace Ui {
class MenuBarWidget;
}

class MenuBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuBarWidget(QWidget *parent = 0);
    ~MenuBarWidget();
    void setCurrentPage(const QString& page);

protected:
    bool event(QEvent *event) override;

private:
    void initPage();
    void addTabs(const QString& page, const QVariantList& listBtn);
    void addSubMenu(const QString& page);

private slots:
    void on_btnGroupClicked(int);
    void on_btnPrePageClicked();
    void on_btnNextPageClicked();

signals:
    void signal_subMenuClicked(const QString&, int);
    void signal_nextSubMenuClicked(const QString&, int, bool&);

private:
    Ui::MenuBarWidget *ui;

    QButtonGroup*		m_pSubMenuGroup{ Q_NULLPTR };	//子菜单按钮组

    int					m_nBtnIndex{ -1 };				//子菜单按钮index
    int					m_nMoveIndex{ 0 };				//子菜单数量超过5之后，需要移动

    QMap<QString, int>	m_mSubMenuPage;					//每个子菜单的buttonID
    QMap<QString, int>	m_mSubMenuCount;				//每个主菜单下面子菜单的数量，主要用来进行界面的移动
    QMap<QString, int>	m_mOffSet;                      //每个子界面移动的距离
    QMap<QString, QAbstractButton*>     m_mCurrentBtn;	//stacked页面选中的按钮
};

#endif // MENU_BAR_WIDGET_H
