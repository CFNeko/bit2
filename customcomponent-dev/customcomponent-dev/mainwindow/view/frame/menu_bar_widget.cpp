#include "menu_bar_widget.h"
#include "ui_menu_bar_widget.h"
#include "menu_defines.h"

#include "menu_button.h"
#include <QDebug>
#include <QScrollBar>

using namespace menu;
MenuBarWidget::MenuBarWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MenuBarWidget)
{
    ui->setupUi(this);
    initPage();
}

MenuBarWidget::~MenuBarWidget()
{
    auto listMenu = m_pSubMenuGroup->buttons();
    for(const auto& menu : listMenu)
    {
        menu->deleteLater();
    }
    for (int nIndex = 0; nIndex < ui->stackedWidget->count(); ++nIndex)
    {
        QWidget* pWidget = ui->stackedWidget->widget(nIndex);
        if (Q_NULLPTR == pWidget)
        {
            continue;
        }
        ui->stackedWidget->removeWidget(pWidget);
        pWidget->deleteLater();
    }

    delete ui;
}

void MenuBarWidget::initPage()
{
    for (int nIndex = 0; nIndex < ui->stackedWidget->count(); ++nIndex)
    {
        auto pWidget = ui->stackedWidget->widget(nIndex);
        if (Q_NULLPTR == pWidget)
        {
            continue;
        }
        ui->stackedWidget->removeWidget(pWidget);
        pWidget->deleteLater();
    }

    m_pSubMenuGroup = new QButtonGroup();
    m_pSubMenuGroup->setExclusive(true);
    connect(m_pSubMenuGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &MenuBarWidget::on_btnGroupClicked);

    ui->btnPageNext->setVisible(false);
    ui->btnPagePre->setVisible(false);
    connect(ui->btnPagePre, &QPushButton::clicked, this, &MenuBarWidget::on_btnPrePageClicked);
    connect(ui->btnPageNext, &QPushButton::clicked, this, &MenuBarWidget::on_btnNextPageClicked);

    ui->scrollArea->horizontalScrollBar()->setSingleStep(130);
    ui->scrollArea->setMinimumWidth(130 * 4);
}

void MenuBarWidget::addTabs(const QString& page, const QVariantList &listBtn)	// 菜单
{
    auto pWidget = new QWidget();
    auto pTabLayout = new QHBoxLayout();
    pTabLayout->setMargin(0);
    pTabLayout->setSpacing(0);
    pTabLayout->setSizeConstraint(QLayout::SetMinimumSize);

    for (const auto& text : listBtn)
    {
        auto btn = new MenuButton(++m_nBtnIndex);
        btn->setFixedSize(130, 44);
        btn->setProperty("buttontype", "submenu");
        btn->setCheckable(true);
        btn->setChecked(false);
        btn->setText(QApplication::translate("QObject", text.toString().toStdString().c_str(), Q_NULLPTR));

        m_pSubMenuGroup->addButton(btn, m_nBtnIndex);
        pTabLayout->addWidget(btn);

        //按钮按下的瞬间发信号去检测页面是否需要提醒
        connect(btn, &MenuButton::signal_btnClicked, this, &MenuBarWidget::signal_nextSubMenuClicked);

        if (listBtn.first() != text.toString())
        {
            continue;
        }
        m_mCurrentBtn.insert(page, btn);	//保证界面有一个默认的选中按钮
    }

    m_mSubMenuCount.insert(page, listBtn.size());

    auto t_spaceItem = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    pTabLayout->addSpacerItem(t_spaceItem);
    pWidget->setLayout(pTabLayout);
    pWidget->setProperty("widgettype", "transparent");
    ui->stackedWidget->addWidget(pWidget);
    int nIndex = ui->stackedWidget->count() - 1;
    m_mSubMenuPage.insert(page, nIndex);
}

void MenuBarWidget::on_btnGroupClicked(int)
{
    auto btn = m_pSubMenuGroup->checkedButton();
    if (Q_NULLPTR == btn)
    {
        return;
    }
    m_mCurrentBtn[m_mSubMenuPage.key(ui->stackedWidget->currentIndex())] = btn;
    emit signal_subMenuClicked(btn->text(), static_cast<MenuButton*>(btn)->id());
}

void MenuBarWidget::on_btnPrePageClicked()
{
    int current = ui->scrollArea->horizontalScrollBar()->value();
    int min = ui->scrollArea->horizontalScrollBar()->minimum();
    int step = ui->scrollArea->horizontalScrollBar()->singleStep();
    int val = (current - step) > min ? (current - step) : min;
    ui->scrollArea->horizontalScrollBar()->setValue(val);

    m_mOffSet[ui->lbPageTitle->property("title").toString()] = val;
}

void MenuBarWidget::on_btnNextPageClicked()
{
    int current = ui->scrollArea->horizontalScrollBar()->value();
    int max = ui->scrollArea->horizontalScrollBar()->maximum();
    int step = ui->scrollArea->horizontalScrollBar()->singleStep();
    int val = (current + step) > max ? max : (current + step);
    ui->scrollArea->horizontalScrollBar()->setValue(current + step);
    m_mOffSet[ui->lbPageTitle->property("title").toString()] = val;
}

void MenuBarWidget::setCurrentPage(const QString& page)
{
    if (!m_mSubMenuPage.contains(page))
    {
        addSubMenu(page);
    }
    ui->stackedWidget->setCurrentIndex(m_mSubMenuPage[page]);

    QString text = QApplication::translate("QObject", page.toStdString().c_str(), Q_NULLPTR);
    ui->lbPageTitle->setText(text);
    ui->lbPageTitle->setProperty("translate", page);

    ui->btnPageNext->setVisible(m_mSubMenuCount[page] > 4);
    ui->btnPagePre->setVisible(m_mSubMenuCount[page] > 4);

    m_mCurrentBtn[page]->click();

    ui->scrollAreaWidgetContents->setMinimumWidth(m_mSubMenuCount[page] * 130);
    ui->scrollArea->horizontalScrollBar()->setValue(m_mOffSet[ui->lbPageTitle->property("title").toString()]);
}

void MenuBarWidget::addSubMenu(const QString &page)
{
    addTabs(page, MenuDefines::instance().m_MenuMap.value(page));
}

bool MenuBarWidget::event(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        auto listMenu = m_pSubMenuGroup->buttons();
        for(const auto& menu : listMenu)
        {
            auto btn = dynamic_cast<MenuButton*>(menu);
            btn->setText(QApplication::translate("Qbject", btn->data().toString().toStdString().c_str(), Q_NULLPTR));
        }

        ui->lbPageTitle->setText(QApplication::translate("QObject", ui->lbPageTitle->property("translate").toString().toStdString().c_str(), Q_NULLPTR));
    }

    return QWidget::event(event);
}
