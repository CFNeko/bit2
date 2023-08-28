#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class ListWidgetItem;
}

class ListWidgetItem : public QWidget
{    Q_OBJECT
     Q_PROPERTY(QString name READ name WRITE setName DESIGNABLE true)

public:
    explicit ListWidgetItem(QWidget *parent = 0);
     ~ListWidgetItem();

    QString name() const;
    void setName(const QString& name);
private:
     Ui::ListWidgetItem *ui;
};

class QListWidgetItem;
class ListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = 0);
    ~ListWidget();


private slots:
    void on_listWidgetClicked(QListWidgetItem* item);

signals:
    void signal_selectedName(const QString& name);
};

#endif // LISTWIDGET_H
