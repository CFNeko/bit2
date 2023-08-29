#ifndef PRESCRIPTIONPATIENT_H
#define PRESCRIPTIONPATIENT_H

#include <QWidget>

namespace Ui {
class PrescriptionPatient;
}

class PrescriptionPatient : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionPatient(QWidget *parent = nullptr);
    ~PrescriptionPatient();

private:
    Ui::PrescriptionPatient *ui;
signals:
    void pptClosed();
protected:
    void closeEvent(QCloseEvent *event) override {
        emit pptClosed();
        QWidget::closeEvent(event);
    }
};

#endif // PRESCRIPTIONPATIENT_H
