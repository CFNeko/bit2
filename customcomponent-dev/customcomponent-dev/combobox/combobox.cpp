#include "combobox.h"
#include "listwidget.h"
#include "tablewidget.h"
#include<QLineEdit>
#include <QDir>
#include <QIcon>
#include <QDebug>

const QString SELECT_TYPE_ICON_PATH("./../../CustomComponent/combobox/image/");

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{

}

ComboBox::~ComboBox()
{

}

void ComboBox::setComboBoxModel(COMBOBOX_MODEL_TYPE model)
{
    if(LIST_MODEL == model)
    {
        m_pList = new ListWidget;
        connect(m_pList, &ListWidget::signal_selectedName, this, &ComboBox::slot_selectedName);
        this->setModel(m_pList->model());
        this->setView(m_pList);
        return;
    }
    if(TABLE_MODEL == model)
    {
        initTableCell();
    }
}

QString ComboBox::text() const
{
    return this->currentText();
}

void ComboBox::setText(const QString &text)
{
    this->setCurrentText(text);
}

void ComboBox::slot_selectedName(const QString &text)
{
    qDebug() << text;
    setText(text);
}

void ComboBox::initTableCell()
{
    m_pBtn = new QPushButton(this);
    m_pBtn->setFlat(true);
    m_pBtn->setProperty("buttontype", "selecticon");

    QDir dir(SELECT_TYPE_ICON_PATH);
    QFileInfoList fileList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);

    QVariantList picList;
    for (const auto& file : fileList)
    {
        picList.append(file.fileName());
    }

    m_pTable = new TableWidget;
    m_pTable->setPath(SELECT_TYPE_ICON_PATH);
    m_pTable->initTable(picList);


    qDebug() << dir.absolutePath();

    connect(m_pTable, &TableWidget::signal_currentIcon, this, &ComboBox::slot_currentIcon);
    this->setModel(m_pTable->model());
    this->setView(m_pTable);
}

void ComboBox::slot_currentIcon(const QString& icon)
{
    m_pBtn->setIcon(QIcon(SELECT_TYPE_ICON_PATH + icon));
    m_Icon = icon;
    this->hidePopup();
}

QVariant ComboBox::icon() const
{
    return m_Icon;
}

void ComboBox::setIcon(const QVariant& icon)
{
    m_pTable->setBtnDisabled(icon.toString());
}
