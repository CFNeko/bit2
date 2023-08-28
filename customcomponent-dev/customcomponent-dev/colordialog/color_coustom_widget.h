#ifndef COLOR_COUSTOM_WIDGET_H
#define COLOR_COUSTOM_WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

class ColorCoustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorCoustomWidget(QWidget *parent = nullptr);
    ~ColorCoustomWidget();

    void setColor(const QColor& color);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
	void initPage();

    void drawBrush(QMouseEvent *event);

signals:
    void signal_color(const QVariant& data);
private:

    QPointF m_ptPointer;
    int m_val;
};

#endif // COLOR_COUSTOM_WIDGET_H
