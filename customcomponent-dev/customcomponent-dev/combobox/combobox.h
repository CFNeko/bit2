#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QVariant>

class ListWidget;
class TableWidget;
class QPushButton;

enum COMBOBOX_MODEL_TYPE{
    LIST_MODEL = 0,
    TABLE_MODEL
};

namespace Ui {
class ComboBox;
}

class ComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText DESIGNABLE true)
    Q_PROPERTY(QVariant icon READ icon WRITE setIcon DESIGNABLE true)

public:
    explicit ComboBox(QWidget *parent = 0);
    ~ComboBox();

    void setComboBoxModel(COMBOBOX_MODEL_TYPE model);

   QString text() const;
   void setText(const QString& text);

   QVariant icon() const;
   void setIcon(const QVariant& icon);

private:
   void initTableCell();

private slots:
   void slot_selectedName(const QString& name);
   void slot_currentIcon(const QString& icon);

private:

   ListWidget* m_pList{ Q_NULLPTR };
   TableWidget* m_pTable{ Q_NULLPTR };
   QPushButton* m_pBtn{ Q_NULLPTR };
   QVariant m_Icon{ QVariant() };

};

#endif // COMBOBOX_H
