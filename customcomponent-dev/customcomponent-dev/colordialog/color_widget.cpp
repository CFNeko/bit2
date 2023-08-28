#include "color_widget.h"
#include "ui_color_widget.h"
#include <QDebug>
ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ColorWidget)
{
    ui->setupUi(this);
    initPage();
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::initPage()
{
    connect(ui->wdgCoustom, &ColorCoustomWidget::signal_color, this, [this](const QVariant& data)
    {
        updateColor(data.value<QColor>());
    });

    connect(ui->sliderVal, &QSlider::valueChanged, this, [this](int val)
    {
        ui->spinVal->setValue(val);

        QColor color;
        color.setHsv(ui->spinHue->value(), ui->spinSat->value(), val);

        ui->spinRed->setValue(color.red());
        ui->spinGreen->setValue(color.green());
        ui->spinBlue->setValue(color.blue());

        ui->lineEdit->setText(color.name(QColor::HexRgb));
        ui->wdgColor->setStyleSheet(QString("background:%1;").arg(ui->lineEdit->text()));

    });

    auto slot_hsv = [this](int val)
    {
        ui->spinRed->blockSignals(true);
        ui->spinGreen->blockSignals(true);
        ui->spinBlue->blockSignals(true);
        QColor color;
        color.setHsv(ui->spinHue->value(), ui->spinSat->value(), ui->spinVal->value());
        updateColor(color);
        ui->wdgCoustom->setColor(color);
        ui->spinRed->blockSignals(false);
        ui->spinGreen->blockSignals(false);
        ui->spinBlue->blockSignals(false);
    };

    auto slot_rgb = [this](int val)
    {
        ui->spinHue->blockSignals(true);
        ui->spinSat->blockSignals(true);
        ui->spinVal->blockSignals(true);
        QColor color;
        color.setRgb(ui->spinRed->value(), ui->spinGreen->value(), ui->spinBlue->value());
        updateColor(color);
        ui->wdgCoustom->setColor(color);
        ui->spinHue->blockSignals(false);
        ui->spinSat->blockSignals(false);
        ui->spinVal->blockSignals(false);
    };

    ui->spinHue->setKeyboardTracking(false);
    ui->spinSat->setKeyboardTracking(false);
    ui->spinVal->setKeyboardTracking(false);
    ui->spinRed->setKeyboardTracking(false);
    ui->spinGreen->setKeyboardTracking(false);
    ui->spinBlue->setKeyboardTracking(false);
    connect(ui->spinHue, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, slot_hsv);
    connect(ui->spinSat, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, slot_hsv);
    connect(ui->spinVal, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, slot_hsv);
    connect(ui->spinVal, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this](int val)
    {
        ui->sliderVal->setValue(val);
    });

    connect(ui->spinRed, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, slot_rgb);
    connect(ui->spinGreen, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, slot_rgb);
    connect(ui->spinBlue, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, slot_rgb);
}

void ColorWidget::updateColor(const QColor &color)
{
    ui->spinRed->setValue(color.red());
    ui->spinGreen->setValue(color.green());
    ui->spinBlue->setValue(color.blue());

    ui->spinHue->setValue(color.hsvHue());
    ui->spinSat->setValue(color.hsvSaturation());
    ui->spinVal->setValue(color.value());

    ui->lineEdit->setText(color.name(QColor::HexRgb));
    ui->wdgColor->setStyleSheet(QString("background:%1;").arg(ui->lineEdit->text()));

    QColor t;
    t.setHsv(color.hsvHue(), color.hsvSaturation(), 255);
    QString qss(QString("QSlider::groove {top:6px;bottom:6px;right: 6px;background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 %1, stop:1#000000);}"
                        "QSlider::handle:vertical{border-image: url(:/resource/slider-handler.png);margin:-6px;}").arg(t.name(QColor::HexRgb)));

    ui->sliderVal->setStyleSheet(qss);
}
