#ifndef RECORDITEMTABLE_H
#define RECORDITEMTABLE_H

#include <QWidget>

#include "prescriptiontable.h"


namespace Ui {
class RecordItemTable;
}

class RecordItemTable : public QWidget
{
    Q_OBJECT

public:
    explicit RecordItemTable(QWidget *parent = nullptr);
    ~RecordItemTable();

private:
    Ui::RecordItemTable *ui;
};

#endif // RECORDITEMTABLE_H
