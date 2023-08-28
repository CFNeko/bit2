#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>


namespace Ui {
class TreeWidget;
}

class QTreeWidgetItem;

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = 0);
    ~TreeWidget();

private:

    void initTree();
    template<typename T>
    QTreeWidgetItem* addChild(T parent, const QString& text);

    void updateParentItemStatus(QTreeWidgetItem* item);
    void updateChildItemStatus(QTreeWidgetItem* item);

private slots:

    void slot_treeItemChanged(QTreeWidgetItem*, int);

private:
    Ui::TreeWidget *ui;
};

#endif // TREEWIDGET_H
