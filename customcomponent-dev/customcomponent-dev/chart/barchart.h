#ifndef BARCHART_H
#define BARCHART_H

#include <QWidget>
#include <QVariantList>
namespace Ui {
class BarChart;
}

class BarChart : public QWidget
{
    Q_OBJECT

public:
    explicit BarChart(QWidget *parent = nullptr);
    ~BarChart();

    void createVerticalChart(const QStringList& categories, const QVariantMap& data, int minimum, int maximum, const QColor& color, const QString& name = QString());
    void createHorizontalChart(const QStringList& categories, const QVariantMap& data, int minimum, int maximum, const QColor& color, const QString& name = QString());
    void createBarsChart(const QStringList& categories, const QVariantMap& data, int minimum, int maximum, const QColor& color, const QString& name = QString());
    void setLineChart(const QVariantList& data)
    {
        m_lineData = data;
    }
private:
    Ui::BarChart *ui;

    QVariantList m_lineData;
};

#endif // BARCHART_H
