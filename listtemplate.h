#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H

#include <QWidget>
#include"msgitem111.h"
#include"ui_msgitem.h"

namespace Ui {
class ListTemplate;
}
class QListWidgetItem;
class MsgItem;

class ListTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit ListTemplate(QWidget *parent = nullptr);
    ~ListTemplate();
private:
    void AddWidgetMsgItem();

/*private slots:
    void slot_selected(MsgItem* pWidget);
    void slot_delete(QWidget *);

    void on_listWidgetClicked(QListWidgetItem* pItem);
    void on_btnAddClicked();
*/

private:
    Ui::ListTemplate *ui;

    MsgItem* m_pCurrentItem{ Q_NULLPTR };

    QListWidgetItem* m_pCurrent{ Q_NULLPTR };

};

#endif // LISTTEMPLATE_H


