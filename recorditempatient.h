#ifndef RECORDITEMPATIENT_H
#define RECORDITEMPATIENT_H

#include <QWidget>

namespace Ui {
class RecordItemPatient;
}

class RecordItemPatient : public QWidget
{
    Q_OBJECT

public:
    explicit RecordItemPatient(QWidget *parent = nullptr);
    ~RecordItemPatient();

private:
    Ui::RecordItemPatient *ui;
signals:
    void rpClosed();
protected:
    void closeEvent(QCloseEvent *event) override {
        emit rpClosed();
        QWidget::closeEvent(event);
    }
};

#endif // RECORDITEMPATIENT_H
