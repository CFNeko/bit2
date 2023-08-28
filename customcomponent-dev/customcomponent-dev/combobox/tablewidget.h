#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVariantList>

class TableWidget : public QTableWidget
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath DESIGNABLE true)

public:
    explicit TableWidget(QWidget *parent = Q_NULLPTR);
    ~TableWidget();

    void initTable(const QVariantList& property);
    void setBtnDisabled(const QString& name);

    QString path() const;
    void setPath(const QString& path);

protected:
    void showEvent(QShowEvent *event) override;

signals:
    void signal_currentIcon(const QString& icon);

private slots:
    void on_itemBtnClicked();

private:
    QPoint m_pCellPos;
    QString m_selectedBtn{QString()};	//当前选中的按钮名称
    QMap<QString, QPushButton*> m_mBtn;

    QString m_iconPath{ QString() };
};

#endif // TABLEWIDGET_H
