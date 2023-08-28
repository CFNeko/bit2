#include "barchart.h"
#include "ui_barchart.h"
#include <QtCharts/QtCharts>

QT_CHARTS_USE_NAMESPACE

BarChart::BarChart(QWidget *parent) : QWidget(parent), ui(new Ui::BarChart)
{
    ui->setupUi(this);
}

BarChart::~BarChart()
{
    delete ui;
}

void BarChart::createVerticalChart(const QStringList& categories, const QVariantMap& data, int minimum, int maximum, const QColor& color, const QString &name)
{
    auto coverValue = [](const QVariantList &data)
    {
        QList<qreal> tb;
        tb.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](QVariant d) { tb.append(d.toReal()); });

        return tb;
    };

    QList<QBarSet *> barSets;
    for(auto dt : data)
    {
        auto barSet = new QBarSet(data.key(dt));
        barSet->append(coverValue(dt.toList()));
        barSet->setColor(color);
        barSet->setBorderColor(color);
        barSet->setLabelColor(color);

        barSets.append(barSet);
    }

    auto barSeries = new QBarSeries(this);
    barSeries->append(barSets);

    auto chart = new QChart();
    chart->addSeries(barSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    if(!m_lineData.isEmpty())
    {
        auto coverLineValue = [](const QVariantList &data)
        {
            QList<QPointF> tb;
            tb.reserve(data.size());
            std::for_each(data.begin(), data.end(), [&](QVariant d) { tb.append(d.toPointF()); });

            return tb;
        };
        auto lineSeries = new QLineSeries();
        lineSeries->append(coverLineValue(m_lineData));
        chart->addSeries(lineSeries);
    }

    auto axisX = new QBarCategoryAxis(this);
    axisX->setGridLineVisible(false);
    axisX->append(categories);

    auto axisY = new QValueAxis(this);
    axisY->setRange(minimum, maximum);
    axisY->setTickCount(6);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisX);
    barSeries->attachAxis(axisY);

    QFont font;
    font.setPixelSize(8);
    axisY->setLabelsFont(font);
    axisX->setLabelsFont(font);
    for(auto p : barSets)
    {
        p->setLabelFont(font);
    }

    barSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    barSeries->setLabelsVisible(true);

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

void BarChart::createHorizontalChart(const QStringList& categories, const QVariantMap& data, int minimum, int maximum, const QColor& color, const QString &name)
{
    auto coverValue = [](const QVariantList &data)
    {
        QList<qreal> tb;
        tb.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](QVariant d) { tb.append(d.toReal()); });

        return tb;
    };

    QList<QBarSet *> barSets;
    for(auto dt : data)
    {
        auto barSet = new QBarSet(data.key(dt));
        barSet->append(coverValue(dt.toList()));
        barSet->setColor(color);
        barSet->setBorderColor(color);
        barSet->setLabelColor(color);

        barSets.append(barSet);
    }

    auto barSeries = new QHorizontalBarSeries(this);
    barSeries->append(barSets);

    auto chart = new QChart();
    chart->addSeries(barSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto axisX = new QBarCategoryAxis(this);
    axisX->setGridLineVisible(false);
    axisX->append(categories);

    auto axisY = new QValueAxis(this);
    axisY->setRange(minimum, maximum);
    axisY->setTickCount(6);

    chart->addAxis(axisX, Qt::AlignLeft);
    chart->addAxis(axisY, Qt::AlignBottom);
    barSeries->attachAxis(axisX);
    barSeries->attachAxis(axisY);

    QFont font;
    font.setPixelSize(8);
    axisY->setLabelsFont(font);
    axisX->setLabelsFont(font);
    for(auto p : barSets)
    {
        p->setLabelFont(font);
    }

    barSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    barSeries->setLabelsVisible(true);

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

void BarChart::createBarsChart(const QStringList &categories, const QVariantMap &data, int minimum, int maximum, const QColor &color, const QString &name)
{
    auto coverValue = [](const QVariantList &data)
    {
        QList<qreal> tb;
        tb.reserve(data.size());
        std::for_each(data.begin(), data.end(), [&](QVariant d) { tb.append(d.toReal()); });

        return tb;
    };

    QList<QBarSet *> barSets;
    for(auto dt : data)
    {
        auto barSet = new QBarSet(data.key(dt));
        barSet->append(coverValue(dt.toList()));
        //barSet->setColor(color);
        //barSet->setBorderColor(color);
        //barSet->setLabelColor(color);

        barSets.append(barSet);
    }

    auto barSeries = new QBarSeries(this);
    auto pbarSeries = new QPercentBarSeries(this);
    barSeries->append(barSets);
    pbarSeries->append(barSets);

    auto chart = new QChart();
    chart->addSeries(barSeries);
    //chart->addSeries(pbarSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto axisX = new QBarCategoryAxis(this);
    axisX->setGridLineVisible(false);
    axisX->append(categories);

    auto axisY = new QValueAxis(this);
    //axisY->setRange(minimum, maximum);
    axisY->setTickCount(6);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisX);
    barSeries->attachAxis(axisY);

    QFont font;
    font.setPixelSize(8);
    axisY->setLabelsFont(font);
    axisX->setLabelsFont(font);

    for(auto p : barSets)
    {
        p->setLabelFont(font);
    }

    barSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    barSeries->setLabelsVisible(true);

    axisY->setLabelFormat("%d");
    axisX->setLabelsColor(QColor("#FFFFFF"));
    axisY->setLabelsColor(QColor("#FFFFFF"));
    axisY->setGridLinePen(QPen(QBrush(QColor("#353A4A")), 1, Qt::DashLine));

    chart->legend()->setVisible(true);
    chart->setBackgroundVisible(false);
    chart->setTitle(name);

    auto chartView = new QChartView(chart, ui->wdgChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(QSize(461, 171));
    ui->chart->addWidget(chartView);
}
