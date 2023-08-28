#include "image_widget.h"
#include "draw_tool_defines.h"
#include "commands.h"
#include <QBitmap>
#include <QPainter>
#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
	initPage();
}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::initPage()
{
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
}

void ImageWidget::setImg(const QVariant &data)
{
    DrawTool::ImageShow oldImg = m_img;
    DrawTool::ImageShow newImg = data;
    m_img = data;

    m_maskOri = QImage(newImg.size, QImage::Format_ARGB32);

    for (int x = 0, w = m_maskOri.width(); x < w; ++x)
    {
        for (int y = 0, h = m_maskOri.height(); y < h; ++y)
        {
            m_maskOri.setPixelColor(x, y, Qt::transparent);
        }
    }

    createRegion();

    m_show = newImg.img.scaled(newImg.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);

    m_mask = m_maskOri.scaled(newImg.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);
}

void ImageWidget::setOperate(const QVariant &data)
{
    DrawTool::DrawToolData oldOp = m_operate;
    DrawTool::DrawToolData newOp = data;
    m_operate = data;

    if (oldOp.back_label_color != newOp.back_label_color || oldOp.pre_label_color != newOp.pre_label_color)
    {
        createRegion(oldOp.pre_label_color == newOp.pre_label_color);
    }

    if (oldOp.diaphaneity != newOp.diaphaneity)
    {
//        DrawTool::ImageShow img = m_img;
//        QImage maskImg = m_maskOri;
//        setImageAlpha(maskImg, newOp.diaphaneity);
//        m_mask = maskImg.scaled(img.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);
    }

    update();

    setCursor(Qt::ArrowCursor);

    if (newOp.operate != DrawTool::DRAW_TOOL_BRUSH)
    {
        return;
    }
    QPixmap pixmap;
    if (newOp.stroke == DrawTool::BrushStroke::CIRCLE)
    {
        pixmap.load(":/mouse/brush_stroke_circle.png");
    }
    else if (newOp.stroke == DrawTool::BrushStroke::RECT)
    {
        pixmap.load(":/mouse/brush_stroke_rect.png");
    }
    pixmap = pixmap.scaled(pixmap.size() * newOp.width * 0.1, Qt::KeepAspectRatio, Qt::FastTransformation);
    setCursor(pixmap);
}

auto ImageWidget::updateImage(const QImage& img) ->void
{
    m_maskOri = img;
    DrawTool::ImageShow tmp = m_img;
    m_mask = img.scaled(tmp.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);
    createRegion(true);
    update();
}

void ImageWidget::createRegion(bool back)
{
    DrawTool::DrawToolData op = m_operate;
    DrawTool::ImageShow tmp = m_img;

    QImage imgRegion(m_maskOri.size(), QImage::Format_MonoLSB);

    for (int x = 0, w = imgRegion.width(); x < w; ++x)
    {
        for (int y = 0, h = imgRegion.height(); y < h; ++y)
        {
            imgRegion.setPixel(x, y, op.all ? 0 : (m_maskOri.pixelColor(x, y) == op.back_label_color ? 0 : 1));
        }
    }

    QBitmap bp = QBitmap::fromImage(imgRegion.scaled(m_maskOri.size() * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation));
    QRegion region(bp);
    m_region.swap(region);

    imgRegion.save("./region.png");

    if (back)
    {
        for (int x = 0, w = imgRegion.width(); x < w; ++x)
        {
            for (int y = 0, h = imgRegion.height(); y < h; ++y)
            {
                imgRegion.setPixel(x, y, m_maskOri.pixelColor(x, y) == op.pre_label_color ? 0 : 1);
            }
        }
        QBitmap bpc = QBitmap::fromImage(imgRegion.scaled(m_maskOri.size() * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation));
        QRegion regionBak(bpc);
        m_backregion.swap(regionBak);
    }
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QSize sizeImg = size();
    QImage imgBack(sizeImg, QImage::Format_ARGB32);
    imgBack.fill(Qt::black);

    DrawTool::ImageShow img = m_img;
    DrawTool::DrawToolData op = m_operate;

    QImage imgDraw(img.size, QImage::Format_ARGB32);
    imgDraw.fill(Qt::transparent);
    m_draw = imgDraw.scaled(img.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);

    drawPolygon();

    QImage mask;
    drawMaskAlpha(mask);

    QPainter painter;
    painter.begin(&imgBack);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(m_paintPt, m_show);
    painter.drawImage(m_paintPt, m_draw);
    painter.drawImage(m_paintPt, mask);


//    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
//    painter.fillRect(imgBack.rect(), QColor(0, 0, 0, op.diaphaneity));
    painter.end();

    painter.begin(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(QPoint(0, 0), imgBack);
    painter.end();
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    m_button = event->button();
    DrawTool::DrawToolData op = m_operate;
    if (op.operate == DrawTool::DRAW_TOOL_BRUSH && event->button() == Qt::LeftButton)
    {
        drawBrush(event);
        return;
    }
    if(op.operate == DrawTool::DRAW_TOOL_DRAWMOVE &&  event->button() == Qt::LeftButton)
    {
        dragMove(event);
    }
    if(op.operate == DrawTool::DRAW_TOOL_DRAWMOVE &&  event->button() == Qt::RightButton)
    {
        zoomImage(event);
    }
    if(op.operate == DrawTool::DRAW_TOOL_POLYGON &&  event->button() == Qt::LeftButton)
    {
        drawPolygon(event);
    }
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    DrawTool::DrawToolData op = m_operate;
    if (op.operate == DrawTool::DRAW_TOOL_BRUSH)
    {
        drawBrush(event);
        return;
    }
    if(op.operate == DrawTool::DRAW_TOOL_DRAWMOVE)
    {
        if (m_button == Qt::RightButton)
        {
            zoomImage(event);
        }
        else if (m_button == Qt::LeftButton)
        {
            dragMove(event);
        }
    }
    if(op.operate == DrawTool::DRAW_TOOL_POLYGON)
    {
        drawPolygon(event);
    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    DrawTool::DrawToolData op = m_operate;
    if (op.operate == DrawTool::DRAW_TOOL_BRUSH)
    {
        drawBrush(event);
        return;
    }
    if(op.operate == DrawTool::DRAW_TOOL_DRAWMOVE)
    {
        if (m_button == Qt::RightButton)
        {
            zoomImage(event);
        }
        else if (m_button == Qt::LeftButton)
        {
            dragMove(event);
        }
    }

    if(op.operate == DrawTool::DRAW_TOOL_POLYGON)
    {
        drawPolygon(event);
    }
}

void ImageWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        fillPolygon();
    }

    if (event->modifiers() == Qt::ControlModifier && (event->key() == Qt::Key_Z || event->key() == Qt::Key_Y))
    {
        CommandStack::instance().keyEvent(event);
    }
}

void ImageWidget::wheelEvent(QWheelEvent *event)
{
    int degrees = event->delta() / 8;
    int steps = degrees / 15;

    DrawTool::DrawToolData op = m_operate;
    if(op.operate == DrawTool::DRAW_TOOL_BRUSH)
    {
        op.width = op.width + steps;
        op.width = qMax(1, qMin(op.width, BRUSH_WIDTH_MAX));

        m_operate = op;

        QPixmap pixmap(10, 10);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        QPen pen = QPen(QColor(op.pre_label_color), 1, Qt::DashLine, Qt::RoundCap);
        if (op.stroke == DrawTool::BrushStroke::CIRCLE)
        {
            painter.drawRect(QRect(0, 0, 9, 9));
            //pixmap.load(":/mouse/img/tagged/mouse/brush_stroke_circle.png");
        }
        else if (op.stroke == DrawTool::BrushStroke::RECT)
        {
             painter.drawArc(QRect(0, 0, 10, 10), 5, 5);
            //pixmap.load(":/mouse/brush_stroke_rect.png");
        }
        pixmap = pixmap.scaled(pixmap.size() * op.width * 0.1, Qt::KeepAspectRatio, Qt::FastTransformation);
        setCursor(pixmap);
    }
}

void ImageWidget::zoomImage(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        m_brushPt = event->pos();
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QPointF pt = event->pos() - m_brushPt;
        m_dScale = m_dScale - pt.y() * 0.0032;
        if (m_dScale <= 0.1)
        {
            m_dScale = 0.1;
        }

        QPointF tmp = transWindowPosToPicture(event->pos());
        m_paintPt = event->pos() - tmp * m_dScale;

        DrawTool::ImageShow img = m_img;
        m_show = img.img.scaled(img.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);
        m_mask = m_maskOri.scaled(img.size * m_dScale, Qt::KeepAspectRatio, Qt::FastTransformation);
        update();

        m_brushPt = event->pos();
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        m_brushPt = QPoint(0, 0);
    }
}

void ImageWidget::dragMove(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
        {
            m_brushPt = event->pos();
        }
        else if (event->type() == QEvent::MouseMove)
        {
            QPointF pt = event->pos() - m_brushPt;
            m_paintPt += pt;
            update();

            m_brushPt = event->pos();
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            m_brushPt = QPoint(0, 0);
        }
}

void ImageWidget::drawBrush(QMouseEvent *event)
{
    DrawTool::DrawToolData op = m_operate;
    QPen pen = QPen(QColor(op.pre_label_color), op.width, Qt::DashLine, Qt::RoundCap);
    pen.setCapStyle(op.stroke == DrawTool::BrushStroke::RECT ? Qt::SquareCap : Qt::RoundCap);

    QPainter painter(&m_mask);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setClipRegion(m_region);
    if (m_button == Qt::RightButton)
    {
        painter.setClipRegion(m_backregion);
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
    }
    painter.setPen(pen);

    if (event->type() == QEvent::MouseButtonPress)
    {
        m_brushPt = event->pos();
        painter.drawPoint(transPicPosToWindowWithoutOffset(transWindowPosToPicture(event->pos())));
    }
    if (event->type() == QEvent::MouseMove)
    {
        painter.drawLine(transPicPosToWindowWithoutOffset(transWindowPosToPicture(m_brushPt)),
                 transPicPosToWindowWithoutOffset(transWindowPosToPicture(event->pos())));
        m_brushPt = event->pos();
    }
    if (event->type() == QEvent::MouseButtonRelease)
    {
        m_brushPt = QPoint(-1, -1);
    }

    painter.end();

    if (event->type() == QEvent::MouseButtonRelease)
    {
       updateImageCache();
    }

    update();
}

void ImageWidget::drawPolygon(QMouseEvent* event)
{
    DrawTool::Polygon polygon = m_polygon;

    if (event->type() == QEvent::MouseButtonPress)
    {
        polygon.clear();
        m_pressed = true;
        polygon.pts.push_back(event->pos());
    }
    if (event->type() == QEvent::MouseMove && m_pressed)
    {
        polygon.pts.push_back(event->pos());
    }
    if (event->type() == QEvent::MouseButtonRelease)
    {
        polygon.paintend = true;
        m_pressed = false;
        polygon.pts.push_back(polygon.pts.at(0));
    }

    m_polygon = polygon;
    update();
}

void ImageWidget::drawPolygon()
{
    DrawTool::DrawToolData op = m_operate;
    if (op.operate != DrawTool::DRAW_TOOL_POLYGON)
    {
        return;
    }
    DrawTool::Polygon polygon = m_polygon;
    if (polygon.pts.isEmpty())
    {
        return;
    }
    DrawTool::ImageShow img = m_img;
    if (polygon.filled)
    {
        return;
    }
    QPen pen = QPen(QColor(op.pre_label_color), polygon.width * m_dScale, Qt::SolidLine, Qt::RoundCap);
    for (auto it = polygon.pts.begin(); it != polygon.pts.end(); ++it)
    {
        drawPoint(transPicPosToWindowWithoutOffset(transWindowPosToPicture(*it)), pen);
        if (it != polygon.pts.begin())
        {
            drawLine(transPicPosToWindowWithoutOffset(transWindowPosToPicture(*(it - 1))),
                transPicPosToWindowWithoutOffset(transWindowPosToPicture(*it)), pen);
        }
    }
}

void ImageWidget::fillPolygon()
{
    DrawTool::DrawToolData op = m_operate;
    if (op.operate != DrawTool::DRAW_TOOL_POLYGON)
    {
        return;
    }
    DrawTool::Polygon polygon = m_polygon;

    if (polygon.filled)
    {
        return;
    }

    QVector<QPointF> pts;

    std::for_each(polygon.pts.begin(), polygon.pts.end(), [&](QPointF pt)
    {
        pts.push_back(transPicPosToWindowWithoutOffset(transWindowPosToPicture(pt)));
    });

    QPolygonF plyf(pts);
    QPainterPath path;
    path.addPolygon(plyf);
    QPen pen = QPen(QColor(op.pre_label_color), polygon.width * m_dScale, Qt::SolidLine, Qt::RoundCap);

    QPainter painter(&m_mask);
    painter.setPen(pen);
    painter.setClipRegion(m_region);
    painter.setBrush(QColor(op.pre_label_color));
    painter.drawPath(path);
    painter.end();

    polygon.filled = true;
    m_polygon = polygon;

    updateImageCache();
}

void ImageWidget::drawPoint(const QPointF& pt, const QPen& pen)
{
    QPainter painter(&m_draw);
    painter.setPen(pen);
    painter.drawPoint(pt);
    update();
}

void ImageWidget::drawLine(const QPointF& spt, const QPointF& ept, const QPen& pen)
{
    QPainter painter(&m_draw);
    painter.setPen(pen);
    painter.drawLine(spt, ept);
    update();
}

void ImageWidget::drawLines(const QVector<QPointF>& pts, const QPen& pen)
{
    QPainter painter(&m_draw);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.drawLines(pts);
    update();
}

void ImageWidget::updateImageCache()
{
    DrawTool::ImageShow img = m_img;

    QImage tmp = imgScaled(img.size, m_mask);
    CommandStack::instance().push(m_maskOri, tmp, this);
    m_maskOri = std::move(tmp);
}

QPointF ImageWidget::transWindowPosToPicture(const QPointF& pt)
{
    QPointF offset = pt - m_paintPt;
    return offset / m_dScale;
}

QPointF ImageWidget::transPicPosToWindowWithoutOffset(const QPointF& pt)
{
    return pt * m_dScale;
}

QImage ImageWidget::imgScaled(const QSize& size, const QImage& img, Qt::AspectRatioMode aspectMode, Qt::TransformationMode mode)
{
    QSize newSize = img.size();

    qint64 rw = qint64(size.height()) * qint64(newSize.width()) / qint64(newSize.height());
    bool useHeight = aspectMode == Qt::KeepAspectRatio ? (rw <= size.width()) : (rw >= size.width());

    if (useHeight)
    {
        newSize = QSize(rw, qint64(newSize.height()));
    }
    else
    {
        newSize = QSize(size.width(), qint32(qint64(size.width()) * qint64(newSize.height()) / qint64(newSize.width())));
    }

    newSize.rwidth() = qMax(size.width(), qMax(newSize.width(), 1));
    newSize.rheight() = qMax(size.height(), qMax(newSize.height(), 1));

    QTransform wm = QTransform::fromScale((qreal)newSize.width() / img.width(), (qreal)newSize.height() / img.height());
    QImage t = img.transformed(wm, mode);
    return t;
}

void ImageWidget::setImageAlpha(QImage& img, int val)
{
    for (int r = 0, wd = img.width(); r < wd; ++r)
    {
        for (int c = 0, ht = img.height(); c < ht; ++c)
        {
            QColor color = img.pixelColor(r, c);
            if (color != Qt::transparent)
            {
                color.setAlpha(val);
                img.setPixelColor(r, c, color);
            }
        }
    }
}

void ImageWidget::drawMaskAlpha(QImage& img)
{
    DrawTool::DrawToolData op = m_operate;
    QImage back(m_mask.size(), QImage::Format_ARGB32);
    back.fill(Qt::transparent);
    img = back;
    QPainter pter(&img);
    pter.setCompositionMode(QPainter::CompositionMode_Source);
    pter.drawImage(0, 0, m_mask);
    pter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    pter.fillRect(back.rect(), QColor(0, 0, 0, op.diaphaneity));
    pter.end();
}
