#include "listtemplate.h"
#include "ui_listtemplate.h"
#include"msgitem111.h"
#include"msgitem111.h"
#include"ui_msgitem.h"

ListTemplate::ListTemplate(QWidget *parent) : QWidget(parent), ui(new Ui::ListTemplate)
{
    ui->setupUi(this);

}

ListTemplate::~ListTemplate()
{
    delete ui;
}

/*void ListTemplate::AddWidgetMsgItem()
{
    auto pMsgItem = new MsgItem();
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint( QSize(360, 70));
    pMsgItem->setCount(99);
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, pMsgItem);

    connect(pMsgItem, &MsgItem::signal_selected, this, &ListTemplate::slot_selected);
    connect(pMsgItem, &MsgItem::signal_delete, this, &ListTemplate::slot_delete);
}
*/

/*
//第一种选中的实现方式
void ListTemplate::slot_selected(MsgItem *pWidget)
{
    if(Q_NULLPTR == pWidget)
    {
        return;
    }
    if(Q_NULLPTR != m_pCurrentItem)
    {
         m_pCurrentItem->selected(false);
    }

    pWidget->selected(true);
    m_pCurrentItem = pWidget;
}

//第二种选中的实现方式
void ListTemplate::on_listWidgetClicked(QListWidgetItem *pItem)
{
    if (Q_NULLPTR == pItem)
    {
        return;
    }
    if (Q_NULLPTR == m_pCurrent)
    {
        m_pCurrent = pItem;
        auto item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
        if (Q_NULLPTR == item)
        {
            return;
        }
        item->selected(true);
        return;
    }
    auto item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(m_pCurrent));
    if (Q_NULLPTR == item)
    {
        return;
    }
    item->selected(false);
    m_pCurrent = pItem;
    item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
    if (item == Q_NULLPTR)
    {
        return;
    }
    item->selected(true);
}

void ListTemplate::slot_delete(QWidget* pWidget)
{
    delete pWidget;
    pWidget = Q_NULLPTR;
    QListWidgetItem *pItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
    m_pCurrentItem = Q_NULLPTR;
    m_pCurrent = Q_NULLPTR;
}

void ListTemplate::on_btnAddClicked()
{
    AddWidgetMsgItem();
}
*/
