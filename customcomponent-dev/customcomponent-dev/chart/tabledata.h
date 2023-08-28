#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QWidget>
#include <QAbstractTableModel>

class TableModel : public  QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    ~TableModel();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void updateData(const QVariantList& data = QVariantList())
    {
        m_data = data;
        m_row = data.size();
    }

    void setHeader(const QVariantList& header = QVariantList())
    {
        m_header = header;
        m_column = header.size();
    }

    void setColor(const QVariantList& color = QVariantList())
    {
        m_color = color;
    }
private:
    int m_row;
    int m_column;
    QVariantList m_data;
    QVariantList m_header;
    QVariantList m_color;
};

namespace Ui {
class TableData;
}

class TableData : public QWidget
{
    Q_OBJECT

public:
    explicit TableData(QWidget *parent = nullptr);
    ~TableData();

    void updateData(const QVariantList& data = QVariantList())
    {
       m_pMode->updateData(data);
    }

    void setHeader(const QVariantList& header)
    {
        m_pMode->setHeader(header);
    }

    void setColor(const QVariantList& color)
    {
        m_pMode->setColor(color);
    }

    void setcolumnWidth(const QVariantList& width);

private:
    Ui::TableData *ui;
    TableModel* m_pMode{ Q_NULLPTR };
};

#endif // TABLEDATA_H
