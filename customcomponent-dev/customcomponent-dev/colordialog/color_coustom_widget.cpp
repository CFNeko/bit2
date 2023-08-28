#include "color_coustom_widget.h"
#include <QPainter>
#include <QDebug>

ColorCoustomWidget::ColorCoustomWidget(QWidget *parent) : QWidget(parent), m_val(255), m_ptPointer(QPoint(0,0))
{
	initPage();
}

ColorCoustomWidget::~ColorCoustomWidget()
{

}

void ColorCoustomWidget::initPage()
{
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
}


void ColorCoustomWidget::paintEvent(QPaintEvent *event)
{
    QImage back(size(), QImage::Format_ARGB32);
    back.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&back);
    QPen pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);

    QLineF line1(m_ptPointer.x() - 5, m_ptPointer.y(), m_ptPointer.x() + 5, m_ptPointer.y());
    QLineF line2(m_ptPointer.x(), m_ptPointer.y() - 5, m_ptPointer.x(), m_ptPointer.y() + 5);
    painter.drawLine(line1);
    painter.drawLine(line2);

    painter.end();

    painter.begin(this);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    QLinearGradient linearGradientH(this->rect().topLeft(), this->rect().topRight());
    linearGradientH.setSpread(QGradient::PadSpread);

    linearGradientH.setColorAt((qreal)0, QColor(255, 0, 1, 255));
    linearGradientH.setColorAt((qreal)1 / 6, QColor(255, 0, 255, 255));
    linearGradientH.setColorAt((qreal)1 / 3, QColor(0, 0, 255, 255));
    linearGradientH.setColorAt((qreal)1 / 2, QColor(0, 255, 255, 255));
    linearGradientH.setColorAt((qreal)2 / 3, QColor(0, 255, 0, 255));
    linearGradientH.setColorAt((qreal)5 / 6, QColor(255, 255, 0, 255));
    linearGradientH.setColorAt(1, QColor(255, 0, 0, 255));
    painter.fillRect(this->rect(), linearGradientH);

    QLinearGradient linearGradientV(this->rect().topLeft(), this->rect().bottomLeft());
    linearGradientV.setColorAt(0, QColor(0, 0, 0, 0));
    linearGradientV.setColorAt(1, QColor(255, 255, 255, 255));
    linearGradientV.setSpread(QGradient::PadSpread);
    painter.fillRect(this->rect(), linearGradientV);

    painter.drawImage(0, 0, back);

    painter.end();
}

void ColorCoustomWidget::mousePressEvent(QMouseEvent *event)
{
    drawBrush(event);
}

void ColorCoustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    drawBrush(event);
}

void ColorCoustomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    drawBrush(event);
}

void ColorCoustomWidget::showEvent(QShowEvent *event)
{
    m_ptPointer = QPointF(size().width(), size().height());
    QColor t;
    t.setHsv(359* (1 - (qreal)m_ptPointer.rx() / size().width()), 255 * (1 - (qreal)m_ptPointer.ry() / size().height()), m_val);

    emit signal_color(t);
}

void ColorCoustomWidget::setColor(const QColor& color)
{
    int hue = color.hsvHue();
    int sat = color.hsvSaturation();
    m_val = color.value();
    int rx = size().width() * (1 - (qreal)hue / 359);
    int ry = size().height() * (1 - (qreal)sat / 255);

    m_ptPointer.setX(rx);
    m_ptPointer.setY(ry);

    update();
}

void ColorCoustomWidget::drawBrush(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        m_ptPointer = event->pos();
    }
    else if (event->type() == QEvent::MouseMove)
    {
        m_ptPointer = event->pos();
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
    }

    m_ptPointer.setX(qMax(0, qMin((int)m_ptPointer.rx(), size().width())));
    m_ptPointer.setY(qMax(0, qMin((int)m_ptPointer.ry(), size().height())));
    update();
    QColor t;
    t.setHsv(359* (1 - (qreal)m_ptPointer.rx() / size().width()), 255 * (1 - (qreal)m_ptPointer.ry() / size().height()), m_val);

    emit signal_color(t);

}
