#ifndef PIECHART_H
#define PIECHART_H

#include <QWidget>
#include <QtCharts/QtCharts>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class PieChart;
}

class PieChart : public QWidget
{
    Q_OBJECT

public:
    explicit PieChart(QWidget *parent = nullptr);
    ~PieChart();

    void createChart(const QVariantMap& data, const QString& name = QString(), const QColor& color = QColor());

private:
    Ui::PieChart *ui;
    QPieSlice* m_slice{ Q_NULLPTR };
};

#endif // PIECHART_H
