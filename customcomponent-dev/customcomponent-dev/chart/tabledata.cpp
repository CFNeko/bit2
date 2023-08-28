#include "tabledata.h"
#include "ui_tabledata.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

TableModel::~TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_row;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
return m_column;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayRole != role)
    {
        return QVariant();
    }
    if(m_header.isEmpty())
    {
        return QVariant();
    }
    if(orientation == Qt::Horizontal)
    {
        return m_header[section];
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
        case Qt::TextColorRole:
        {
            if(m_color.isEmpty())
            {
                return QVariant();
            }
            return m_color[index.column()];
        }
        case Qt::TextAlignmentRole:
        {
            return int(Qt::AlignHCenter | Qt::AlignVCenter);
        }
        case Qt::DisplayRole:
        {
            if(m_data.isEmpty())
            {
                return QVariant();
            }
            return m_data[index.row()].toList()[index.column()];
        }
    }
    return QVariant();
}


TableData::TableData(QWidget *parent) : QWidget(parent), ui(new Ui::TableData)
{
    ui->setupUi(this);

    m_pMode = new TableModel(ui->tableView);
    ui->tableView->setModel(m_pMode);
}

TableData::~TableData()
{
    delete ui;
}

void TableData::setcolumnWidth(const QVariantList &width)
{
    for(int index = 0; index < width.size(); ++index)
    {
       ui->tableView->setColumnWidth(index, width[index].toInt());
    }
}
