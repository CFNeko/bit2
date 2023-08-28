#ifndef TABLE_WIDGET_H
#define TABLE_WIDGET_H

#include "table_defines.h"
#include <QWidget>
#include <QAbstractItemView>
namespace Ui {
class TableWidget;
}

class QButtonGroup;

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = nullptr);
    ~TableWidget();

    void initTableHeader(const QStringList& header, bool check = true);
	void initTableSortColumn(const QList<int>& sort) const;
    void initTableColumnWidth(const QList<int>& width) const;

    void setTableData(const QList<QVariantList>& data);
    void data(QList<QVariantList>& data, bool header = true, bool index = false) const;

    void setTableCellData(int r, int c, const QVariant& value) const;
    void setTableColumnData(int c, const QVariant& value) const;

	void setTableCellOperate(int r, int c, const QVariant& operate, const QVariant& data = QVariant());
	void setTableColumnOperate(int c, const QVariantList& operate, const QVariant& data = QVariant());
	void setTableColumnOperates(int c, const QVariantList& operates, const QVariant& data = QVariant());

	void setEditTriggerMode(const QAbstractItemView::EditTriggers& mode) const;

	void searchRowByField(const QVariant& field, const QVariant& target);

	void deleteRow();
	void deleteRow(const QVariant& data);

private:
    void initPage();
    QWidget* newBtnCheckBox(const QString& strText, bool header = false) const;
	void initTableData(const QList<QVariantList>& data);
	void updateTableUserOPerate();
	void updateTableData(const QList<QVariantList>& data);

private slots:
    void on_btnCheckClicked() const;


signals:
    void signal_rowData(const QVariantList& list);
	void signal_operate(const QVariant& text, const QVariant& data);

private:
    Ui::TableWidget *ui;
	bool m_check{ true };
    QList<QVariantList> m_data;
    QList<QVariantList> m_searchedDt;
    QList<UserOperate::UserOperater> m_operates;
//	QList<QVariantList> m_data{};	//设置缓存的目的是为了提供搜索的功能
//	QList<QVariantList> m_searchedDt{};	//搜索数据
//	QList<UserOperate::UserOperater> m_operates{};	//缓存表格中的用户操作
	QButtonGroup* m_btnGroup{ Q_NULLPTR };
};

#endif // TABLE_WIDGET_H
