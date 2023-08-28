#include "treewidget.h"
#include "ui_treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TreeWidget)
{
    ui->setupUi(this);
    initTree();
}

TreeWidget::~TreeWidget()
{
    delete ui;
}

template<typename T>
QTreeWidgetItem* TreeWidget::addChild(T parent, const QString& text)
{
    auto item = new QTreeWidgetItem(parent, QStringList(text));
    item->setCheckState(0, Qt::Unchecked);
    return item;
}

void TreeWidget::initTree()
{
    auto item = addChild(ui->tree, "top");
    QList<QTreeWidgetItem*> listChild;
    for(int nIndex = 1; nIndex <= 5; ++nIndex)
    {
        auto pItem = addChild(item, QString("child%1").arg(nIndex));
        listChild.append(pItem);
    }

    for(const auto& child : listChild)
    {
        for(int nRet = 1; nRet <= 5; ++nRet)
        {
            addChild(child, QString("grandchild%1").arg(nRet));
        }
    }
    ui->tree->expandAll();
}

void TreeWidget::updateParentItemStatus(QTreeWidgetItem* item)
{
    auto parent = item->parent();
    if (Q_NULLPTR == parent)
    {
        return;
    }

    parent->setCheckState(0, item->checkState(0));

    int nCount = parent->childCount();
    for (int nIndex = 0; nIndex < nCount; ++nIndex)
    {
        auto child = parent->child(nIndex);
        if (child->checkState(0) != parent->checkState(0))
        {
            parent->setCheckState(0, Qt::PartiallyChecked);
            break;
        }
    }

    updateParentItemStatus(parent);
}

void TreeWidget::updateChildItemStatus(QTreeWidgetItem* item)
{
    int nCount = item->childCount();
    for (int nIndex = 0; nIndex < nCount; ++nIndex)
    {
        auto child = item->child(nIndex);
        child->setCheckState(0, item->checkState(0));
        if (child->childCount() > 0)
        {
            updateChildItemStatus(child);
        }
    }
}

void TreeWidget::slot_treeItemChanged(QTreeWidgetItem* item, int)
{

    updateChildItemStatus(item);
    updateParentItemStatus(item);
}
