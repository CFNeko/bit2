#include "linechart.h"
#include "ui_linechart.h"

#include <QtCharts/QtCharts>

QT_CHARTS_USE_NAMESPACE

LineChart::LineChart(QWidget *parent) : QWidget(parent), ui(new Ui::LineChart)
{
    ui->setupUi(this);
}

LineChart::~LineChart()
{
    delete ui;
}

void LineChart::createChart(const QStringList& categories, const QVariantList& data, int minimum, int maximum, const QColor& color, const QString& name)
{
    auto coverValue = [](const QVariantList &data)
    {
        QList<QPointF> tb;
        tb.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](QVariant d) { tb.append(d.toPointF()); });

        return tb;
    };

    auto lineseries = new QLineSeries();
    lineseries->setName(name);
    lineseries->append(coverValue(data));
    lineseries->setColor(color);
    //lineseries->setLabelColor(color);

    auto chart = new QChart();
    chart->addSeries(lineseries);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto axisX = new QBarCategoryAxis(this);
    axisX->setGridLineVisible(false);
    axisX->append(categories);

    auto axisY = new QValueAxis(this);
    axisY->setRange(minimum, maximum);
    axisY->setTickCount(6);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    lineseries->attachAxis(axisX);
    lineseries->attachAxis(axisY);

    QFont font;
    font.setPixelSize(8);
    axisY->setLabelsFont(font);
    axisX->setLabelsFont(font);

   // lineseries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    //lineseries->setLabelsVisible(true);

    axisY->setLabelFormat("%d");
    axisX->setLabelsColor(QColor("#FFFFFF"));
    axisY->setLabelsColor(QColor("#FFFFFF"));
    axisY->setGridLinePen(QPen(QBrush(QColor("#353A4A")), 1, Qt::DashLine));

    chart->legend()->setVisible(false);
    chart->setBackgroundVisible(false);
    chart->setTitle(name);

    auto chartView = new QChartView(chart, ui->wdgChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(QSize(461, 171));
    ui->chart->addWidget(chartView);
}
