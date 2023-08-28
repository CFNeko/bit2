#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>

namespace Ui {
class LineChart;
}

class LineChart : public QWidget
{
    Q_OBJECT

public:
    explicit LineChart(QWidget *parent = nullptr);
    ~LineChart();

    void createChart(const QStringList& categories, const QVariantList& data, int minimum, int maximum, const QColor& color, const QString& name = QString());

private:
    Ui::LineChart *ui;
};

#endif // LINECHART_H
