#ifndef PRESCRIPTIONTABLE_H
#define PRESCRIPTIONTABLE_H


#include <QWidget>
#include <QMessageBox>

namespace Ui {
class PrescriptionTable;
}

class PrescriptionTable : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionTable(QWidget *parent = nullptr);
    ~PrescriptionTable();

private:
    Ui::PrescriptionTable *ui;
    bool IsLegal();
};

#endif // PRESCRIPTIONTABLE_H
