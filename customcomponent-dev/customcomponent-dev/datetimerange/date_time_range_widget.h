#ifndef DATE_TIME_RANGE_WIDGET_H
#define DATE_TIME_RANGE_WIDGET_H

#include <QWidget>

namespace Ui {
class DateTimeRangeWidget;
}

class DateTimeRangeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeRangeWidget(QWidget *parent = 0);
    ~DateTimeRangeWidget();

signals:
    void signal_dateTime(const QString& strDate);
    void signal_cancel();

private:
    void initPage();

private:
    Ui::DateTimeRangeWidget *ui;
};

#endif // DATE_TIME_RANGE_WIDGET_H
