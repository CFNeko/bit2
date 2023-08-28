#ifndef STATUS_BAR_WIDGET_H
#define STATUS_BAR_WIDGET_H

#include <QWidget>

namespace Ui {
class StatusBarWidget;
}

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget *parent = 0);
    ~StatusBarWidget();

private:
    Ui::StatusBarWidget *ui;
};

#endif // STATUS_BAR_WIDGET_H
