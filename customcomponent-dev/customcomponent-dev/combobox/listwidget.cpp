#include "listwidget.h"
#include "ui_listwidgetitem.h"
#include <QDebug>

ListWidgetItem::ListWidgetItem(QWidget *parent) : QWidget(parent), ui(new Ui::ListWidgetItem)
{
    ui->setupUi(this);
    setWindowFlags( Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint| Qt::WindowSystemMenuHint*/  | Qt::SubWindow );
    setAttribute( Qt::WA_TranslucentBackground, true );
}

ListWidgetItem::~ListWidgetItem()
{
    delete ui;
}

QString ListWidgetItem::name() const
{
    return ui->lbName->text();
}

void ListWidgetItem::setName(const QString& name)
{
    ui->lbName->setText(name);
}

ListWidget::ListWidget(QWidget *parent) : QListWidget(parent)
{
    for(int nIndex = 0; nIndex < 5; ++nIndex)
    {
        auto pItem = new ListWidgetItem();
        pItem->setName(QString("Karson %1").arg(this->count() + 1));
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(240, 50));
        item->setText(pItem->name());
        this->addItem(item);
        this->setItemWidget(item, pItem);
    }
}

ListWidget::~ListWidget()
{
}

void ListWidget::on_listWidgetClicked(QListWidgetItem *item)
{
    auto pItem = dynamic_cast<ListWidgetItem*>(item);
    if(Q_NULLPTR == pItem)
    {
        return;
    }
    emit signal_selectedName(pItem->name());

    qDebug() << pItem->name();
}

