#include "piechart.h"
#include "ui_piechart.h"

#include <QToolTip>
#include <QCursor>

PieChart::PieChart(QWidget *parent) : QWidget(parent), ui(new Ui::PieChart)
{
    ui->setupUi(this);
}

PieChart::~PieChart()
{
    delete ui;
}

void PieChart::createChart(const QVariantMap &data, const QString& name, const QColor &color)
{
    auto series = new QPieSeries();
    connect(series, &QPieSeries::clicked, this, [this](QPieSlice* slice)
    {
        if(slice == m_slice)
        {
            slice->setExploded(!slice->isExploded());
        }
        else
        {
            if(m_slice != Q_NULLPTR)
            {
                m_slice->setExploded(false);
            }

            slice->setExploded();
            m_slice = slice;
        }

        QToolTip::showText(QCursor::pos(), slice->label());
    });

    for(auto val : data)
    {
        auto slice = new QPieSlice();
        slice->setValue(val.toReal());
        slice->setLabelColor(QColor("#FFFFFF"));
        auto label = QString("%1:%2").arg(data.key(val)).arg(val.toReal());
        slice->setLabel(label);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        series->append(slice);
    }

    series->setLabelsVisible(true);
    auto chart = new QChart();

    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->legend()->setVisible(true);
    chart->setBackgroundVisible(false);
    chart->setTitle(name);

    auto chartView = new QChartView(chart, ui->wdgChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->chart->addWidget(chartView);
}
