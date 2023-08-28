#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

#include "base_widget.h"
namespace Ui {
class TestWidget;
}

class TestWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

    virtual bool saveRequest() override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::TestWidget *ui;
};

#endif // TESTWIDGET_H
