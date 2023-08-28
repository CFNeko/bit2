#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVariantMap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList categories;
     categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sept" << "Oct" << "Nov" << "Dec";

    QVariantList val;
    val << 500 << 600 << 243 << 158 << 521 << 465 << 888 << 1310 << 933 << 125 << 445 << 758;

    QVariantMap data;
    data.insert("Jane", val);

    //QVariantList line;
    //line << QPointF(0, 200) << QPointF(1, 403) << QPointF(2, 507) << QPointF(3, 450) << QPointF(4, 485) << QPointF(5, 655)
    //     << QPointF(6, 480) << QPointF(7, 765) << QPointF(8, 587) << QPointF(9, 764) << QPointF(10, 682) << QPointF(11, 998);

    //ui->wdgVer->setLineChart(line);
    ui->wdgVer->createVerticalChart(categories, data, 0, 1400, QColor("#D97559"), "Vertical BarChart Example");
    ui->wdgHori->createHorizontalChart(categories, data, 0, 1400, QColor("#A82694"), "Horizontal BarChart Example");

    QVariantList jane, john, axel, mary, sam;
    jane << 1 << 2 << 3 << 4 << 5 << 6 << 0 << 0 << 0 << 3 << 4 << 16;
    john << 5 << 0 << 0 << 4 << 0 << 7 << 5 << 0 << 7 << 18 << 8 << 3;
    axel << 3 << 5 << 8 << 13 << 8 << 5 << 2 << 4 << 0 << 8 << 2 << 8;
    mary << 5 << 6 << 7 << 3 << 4 << 5 << 6 << 10 << 8 << 5 << 16 << 2;
    sam << 9 << 7 << 5 << 3 << 1 << 2 << 0 << 5 << 0 << 13 << 7 << 5;

    QVariantMap bars;
    bars.insert("Jane", jane);
    bars.insert("John", john);
    bars.insert("Axel", axel);
    bars.insert("Mary", mary);
    bars.insert("Sam", sam);


    ui->wdgBars->createBarsChart(categories, bars, 0, 20, QColor("#D97559"), "Bar Chart Example");

    QVariantMap pie;
    pie.insert("J", 300);
    pie.insert("H", 150);
    pie.insert("K", 65);
    pie.insert("G", 458);
    pie.insert("P", 204);

    ui->wdgPie->createChart(pie, "PieChart Example");

    QVariantList line;
    line << QPointF(0, -200) << QPointF(1, 403) << QPointF(2, -507) << QPointF(3, -450) << QPointF(4, 485) << QPointF(5, 655)
         << QPointF(6, 480) << QPointF(7, -765) << QPointF(8, 587) << QPointF(9, -764) << QPointF(10, 682) << QPointF(11, -998);
    ui->wdgLine->createChart(categories, line, -1000, 1000, QColor("#D97559"), "LineChart Example");



    QVariantList color;
    color << QColor("#FFFFFF") << QColor("#FFFFFF") << QColor("#FACC14") << QColor("#FACC14") << QColor("#FACC14") << QColor("#FFFFFF");
    QVariantList width;
    width << 80 << 100 << 80 << 80 << 100 << 100;

    QVariantList headers;
    headers << "id" << "name" << "addr" << "score" << "class" << "ranking";

    ui->wdgTable->setcolumnWidth(width);
    ui->wdgTable->setColor(color);
    ui->wdgTable->setHeader(headers);

    QVariantList tbData;

    QVariantList row1, row2, row3, row4;

    row1 << "120412" << "wangwu" << "AAAAA" << "70" << "8" << "31";
    row2 << "120413" << "zhangsan" << "AAAAA" << "40" << "6" << "32";
    row3 << "120414" << "lisi" << "AAAAA" << "20" << "4" << "33";
    row4 << "120415" << "zhaoliu" << "AAAAA" << "50" << "2" << "34";

    for(int index = 0; index <= 30; ++index)
    {
        tbData.append(QVariant(row1));
        tbData.append(QVariant(row2));
        tbData.append(QVariant(row3));
        tbData.append(QVariant(row4));
    }

    ui->wdgTable->updateData(tbData);

}

MainWindow::~MainWindow()
{
    delete ui;
}

