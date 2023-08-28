#ifndef MASK_WIDGET_H
#define MASK_WIDGET_H

#include <QDialog>

namespace Ui {
class MaskWidget;
}

class MaskWidget : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QStringList names READ names WRITE setNames DESIGNABLE true)
public:
    static MaskWidget *instance();

    void setMainWidget(QWidget* pWidget);

    QStringList names() const;
    void setNames(const QStringList& names);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    explicit MaskWidget(QWidget *parent = 0);
    ~MaskWidget();

private:
    Ui::MaskWidget *ui;
    QStringList m_listName{ QStringList() };

    QWidget* m_pMainWidget{ Q_NULLPTR };

    static MaskWidget* m_pSelf;
};

#endif // MASK_WIDGET_H
