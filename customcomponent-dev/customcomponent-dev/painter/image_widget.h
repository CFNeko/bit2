#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

    void setImg(const QVariant& data);

    auto img() const ->QVariant
    {
        return m_img;
    }

    void setOperate(const QVariant& data);
    auto operate() const  ->QVariant
    {
        return m_operate;
    }

    auto updateImage(const QImage& img) ->void;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
	void initPage();

    void createRegion(bool back = false);

    void drawBrush(QMouseEvent *event);

    void drawPolygon(QMouseEvent* event);
    void drawPolygon();
    void fillPolygon();

    void zoomImage(QMouseEvent *event);
    void dragMove(QMouseEvent *event);

    void drawPoint(const QPointF& pt, const QPen& pen);
    void drawLine(const QPointF& spt, const QPointF& ept, const QPen& pen);
    void drawLines(const QVector<QPointF>& pts, const QPen& pen);

    QPointF transWindowPosToPicture(const QPointF& pt);
    QPointF transPicPosToWindowWithoutOffset(const QPointF& pt);

    QImage imgScaled(const QSize& size, const QImage& img, Qt::AspectRatioMode aspectMode = Qt::IgnoreAspectRatio,
            Qt::TransformationMode mode = Qt::FastTransformation);

    void updateImageCache();
    void setImageAlpha(QImage& img, int val);
    void drawMaskAlpha(QImage& img);
private:
    QVariant m_img{ QVariant() };
    QVariant m_operate{ QVariant() };
    QVariant m_polygon{ QVariant() };

    bool m_pressed{ false };

    QImage m_show{ QImage() };
    QImage m_draw{ QImage() };
    QImage m_mask{ QImage() };
    QImage m_maskOri{ QImage() };

    QPointF m_brushPt{ QPoint(0, 0) };
    QPointF m_paintPt{ QPoint(0, 0) };
    double m_dScale{ 1.0 };

    Qt::MouseButton m_button{ Qt::NoButton };

    QRegion m_region{ QRegion() };
    QRegion m_backregion{ QRegion() };
};

#endif // IMAGE_WIDGET_H
