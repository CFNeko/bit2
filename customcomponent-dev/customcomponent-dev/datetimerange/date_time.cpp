#include "date_time.h"
#include "ui_date_time.h"

ScrollBar::ScrollBar(QWidget *parent, ScrollType nType) : QWidget(parent), m_nType(nType)
    , m_nCurrentValue(0)
    , m_nOffSet(0)
    , m_nMax(0)
    , m_nMin(0)
    , m_nMousePos(0)
    , m_nDevice(5)
    , m_nStep(1)
{
    this->setFixedSize(parent->size());
}

ScrollBar::~ScrollBar()
{

}

void ScrollBar::setColor(QColor &pColor, ColorType nType)
{
    switch (nType)
    {
    case ColorType::BACKHROUND:
    {
        m_cBackground = pColor;
        break;
    }
    case ColorType::CURRENTTEXT:
    {
        m_cCurrentText = pColor;
        break;
    }
    case ColorType::DISABLETEXT:
    {
        m_cDisableText = pColor;
        break;
    }
    case ColorType::LINE:
    {
        m_cLine = pColor;
        break;
    }
    default:
        break;
    }
}

void ScrollBar::wheelEvent(QWheelEvent *event)
{
    /**滚动的角度,*8就是鼠标滚动的距离**/
    int nDegrees = event->delta() / 8;
    /**滚动的步数,*15就是鼠标滚动的角度**/
    int nSteps = nDegrees / 15;
    int nTarget = m_nType == ScrollType::VERTICAL ? this->height() : this->width();
    m_nOffSet = nTarget / m_nDevice * nSteps;
    update();
}

void ScrollBar::mousePressEvent(QMouseEvent *event)
{
    m_nMousePos = m_nType == ScrollType::VERTICAL ? event->pos().y() : event->pos().x();
    update();
}

void ScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    int nMouserPos = m_nType == ScrollType::VERTICAL ? event->pos().y() : event->pos().x();
    /**判断当前值的大小，如果为范围的极限值则返回**/
    if(m_nCurrentValue == m_nMin && nMouserPos >= m_nMousePos ||
       m_nCurrentValue == m_nMax && nMouserPos <= m_nMousePos)
    {
        return;
    }
    int nTarget = m_nType == ScrollType::VERTICAL ? this->height() : this->width();
    int nOffSet = nMouserPos - m_nMousePos;

    /**判断鼠标移动的距离是否大于最小偏移量 如果大于偏移量 则将偏移量置位最小偏移量 目的是避免界面出现跨越显示**/
    if(nOffSet > (nTarget / m_nDevice))	/**(nTarget / m_nDevice) 为一次偏移的最小值 也就是一个字体的显示的大小边界值**/
    {
        nOffSet = nTarget / m_nDevice;
    }
    else if(nOffSet < -nTarget / m_nDevice)
    {
        nOffSet = -nTarget / m_nDevice;
    }

    /**nOffSet的正负代表便宜的方向**/
    m_nOffSet = nOffSet;
    update();
}

void ScrollBar::mouseReleaseEvent(QMouseEvent *event)
{
    int nTarget = m_nType == ScrollType::VERTICAL ? this->height() : this->width();
    int nOffSet = m_nOffSet;
    /**计算鼠标的偏移量,根据显示字体的控件大小的一半来确定该偏移到那个值(正负表示偏移的方向)**/
    int nJudge = nOffSet < 0 ? -(nTarget / (m_nDevice * 2)) : nTarget / (m_nDevice * 2);
    if(nOffSet < 0)
    {
        if(nOffSet < nJudge)
        {
            m_nOffSet = 0;
            goto UPDATE;
        }
        m_nOffSet = -nTarget / m_nDevice;
        goto UPDATE;
    }
    if (nOffSet < nJudge)
    {
        m_nOffSet = 0;
        goto UPDATE;
    }
    m_nOffSet = nTarget / m_nDevice;

UPDATE:
    update();
}

void ScrollBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    if(m_nMin == m_nMax)
    {
        return;
    }

    /**在绘制界面之前我们需要通过偏移量来计算当前值，毕竟我们的目的是得到值，而不是看着界面做沉思状**/
    int nTarget = m_nType == ScrollType::VERTICAL ? this->height() : this->width();
    int nOffSet = m_nOffSet;
    if(nOffSet >= (nTarget / m_nDevice) && m_nCurrentValue > m_nMin)
    {
        m_nMousePos += nTarget / m_nDevice;
        nOffSet -= nTarget / m_nDevice;
        this->setValue(m_nCurrentValue - m_nStep);
        goto PAINTE;
    }
    else if(nOffSet <= -nTarget / m_nDevice && m_nCurrentValue < m_nMax)
    {
        m_nMousePos -= nTarget / m_nDevice;
        nOffSet += nTarget / m_nDevice;
        this->setValue(m_nCurrentValue + m_nStep);
    }

/**当前值设置完成后，进入界面的绘制**/
PAINTE:
    if(getValue() == m_nMax || getValue() == m_nMin)
    {
        nOffSet = 0;
    }
    m_nOffSet = nOffSet;

    /**首先绘制背景**/
    paintBackground(&painter);
    /**绘制线条 具体的绘制方法后面再说**/
    paintLine(&painter);
    int nFontSize = 14;	/**绘制的字体大小,后面会介绍自动获取字体大小的方法，我在这边定义是由于现实的界面比较大，通过自动获取的字体大小，界面会比较难看**/
    /**绘制当前字体**/
    paintText(&painter, m_nCurrentValue, nOffSet, nFontSize);
    /**绘制两边的字体**/
    for (int nIndex = 1; nIndex <= m_nDevice / 2; ++nIndex)
    {
        nFontSize -= 2;
        if (m_nCurrentValue - m_nStep * nIndex >= m_nMin)
        {
            /**两边字体的偏移量是通过距离计算的**/
            paintText(&painter, m_nCurrentValue - m_nStep * nIndex, nOffSet - nTarget / m_nDevice * nIndex, nFontSize);
        }

        if (m_nCurrentValue + m_nStep * nIndex <= m_nMax)
        {
            paintText(&painter, m_nCurrentValue + m_nStep * nIndex, nOffSet + nTarget / m_nDevice * nIndex, nFontSize);
        }
    }
    /**将父窗口发送目的是能够准确的找到是属于哪个父类(假设界面有多个)**/
    emit signal_currentValueChange(getValue(), this->parentWidget());
}

void ScrollBar::paintBackground(QPainter *pPainter)
{
    pPainter->save();
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(m_cBackground);
    pPainter->drawRect(rect());
    pPainter->restore();
}

void ScrollBar::paintLine(QPainter *pPainter)
{
    int nWidth = this->width();
    int nHeight = this->height();

    pPainter->save();
    pPainter->setBrush(Qt::NoBrush);

    QPen pen = pPainter->pen();
    pen.setWidth(1);
    pen.setColor(m_cLine);
    pen.setCapStyle(Qt::RoundCap);
    pPainter->setPen(pen);

    /**绘制线条需要指定线条的起始坐标, 对于不同类型的滚动屏，坐标也有不同的数值**/

    for(int nIndex = 2; nIndex <= 3; nIndex++)
    {
        /**对于垂直滚动屏来说，线条的Y值是不变的，同理对于水平的滚动屏来说，线条的X值是不变的**/
        int nPosX = m_nType == ScrollType::VERTICAL ? 0 : nWidth / 5 * nIndex;
        int nPosY = m_nType == ScrollType::VERTICAL ? nHeight / 5 * nIndex : 0;
        int nEndPosX = m_nType == ScrollType::VERTICAL ? nHeight : nPosX;
        int nEndPosY = m_nType == ScrollType::VERTICAL ? nPosY : nHeight;

        pPainter->drawLine(nPosX, nPosY, nEndPosX,  nEndPosY);
    }
    pPainter->restore();
}

void ScrollBar::paintText(QPainter *pPainter, int nValue, int nOffSet, int nFontSize)
{
    pPainter->save();

    int nWidth = this->width();
    int nHeight = this->height();
    /**下面注释掉的两行是通过整个界面的长(高)来控制字体的大小**/
//    int nTarget = m_nType == ScrollType::VERTICAL ? this->height() : this->width();
//    font.setPixelSize((nTarget - qAbs(nOffSet)) / m_nDevice);
    QFont font = QFont("Helvetica", 5);
    font.setPixelSize(nFontSize);
    QColor nColor = nOffSet == 0 ? m_cCurrentText : m_cDisableText;
    QPen pen = pPainter->pen();
    pen.setColor(nColor);
    pPainter->setPen(pen);
    pPainter->setBrush(Qt::NoBrush);
    pPainter->setFont(font);

    if(m_nType == ScrollType::HORIZONTAL)
    {
        int textWidth = pPainter->fontMetrics().width(nValue);
        int initX = nWidth / 2 + nOffSet - textWidth / 2;
        pPainter->drawText(QRect(initX, 0, 15, nHeight), Qt::AlignCenter, QString::number(nValue));
        //pPainter->drawText(QRect(initX, 0, textWidth, nHeight), Qt::AlignCenter, QString::number(nValue));
        /**有个小问题，当这儿使用下面的语句时，左边的0和1就会不显示，暂时未纠结其具体原因**/
        goto NEXT;
    }

    int textHeight = pPainter->fontMetrics().height();
    int initY = nHeight / 2 + nOffSet - textHeight / 2;
    pPainter->drawText(QRect(0, initY, nWidth, textHeight), Qt::AlignCenter, QString::number(nValue));

NEXT:
    pPainter->restore();
}



DateTime::DateTime(QWidget *parent) :QWidget(parent), ui(new Ui::DateTime)
{
    ui->setupUi(this);
    initPage();
}

DateTime::~DateTime()
{
    delete ui;
}

void DateTime::initPage()
{
    QColor dColorCurrentText("#43464B");
    QColor dColorLine("#0092FF");
    QColor dColorDisableText("#999999");
    QColor dColorBackground("#FFFFFF");
    QTime time = QTime::currentTime();

   ScrollBar* pWidgetHour = new ScrollBar(ui->widgetHour);
   pWidgetHour->setRang(0, 23);
   pWidgetHour->setValue(time.hour());
   pWidgetHour->setColor(dColorCurrentText);
   pWidgetHour->setColor(dColorLine, ScrollBar::ColorType::LINE);
   pWidgetHour->setColor(dColorDisableText, ScrollBar::ColorType::DISABLETEXT);
   pWidgetHour->setColor(dColorBackground, ScrollBar::ColorType::BACKHROUND);
   connect(pWidgetHour, SIGNAL(signal_currentValueChange(int,QWidget*)), this, SLOT(slot_timeChange(int,QWidget*)));

   ScrollBar* pWidgeMin = new ScrollBar(ui->widgetMin);
   pWidgeMin->setRang(0, 60);
   pWidgeMin->setValue(time.minute());
   pWidgeMin->setColor(dColorCurrentText);
   pWidgeMin->setColor(dColorLine, ScrollBar::ColorType::LINE);
   pWidgeMin->setColor(dColorDisableText, ScrollBar::ColorType::DISABLETEXT);
   pWidgeMin->setColor(dColorBackground, ScrollBar::ColorType::BACKHROUND);
   connect(pWidgeMin, SIGNAL(signal_currentValueChange(int,QWidget*)), this, SLOT(slot_timeChange(int,QWidget*)));

   ScrollBar* pWidgetSec = new ScrollBar(ui->widgetSec);
   pWidgetSec->setRang(0, 60);
   pWidgetSec->setValue(time.hour());
   pWidgetSec->setColor(dColorCurrentText);
   pWidgetSec->setColor(dColorLine, ScrollBar::ColorType::LINE);
   pWidgetSec->setColor(dColorDisableText, ScrollBar::ColorType::DISABLETEXT);
   pWidgetSec->setColor(dColorBackground, ScrollBar::ColorType::BACKHROUND);
   connect(pWidgetHour, SIGNAL(signal_currentValueChange(int,QWidget*)), this, SLOT(slot_timeChange(int,QWidget*)));

   QDateTime date = QDateTime::currentDateTime();
   ui->dateEdit->setDate(date.date());
   ui->dateEdit->setTime(date.time());
}

/**接收信号的槽函数**/
void DateTime:: slot_timeChange(int nValue, QWidget* pWidget)
{
    QTime time = ui->timeEdit->time();
    int nHour = pWidget == ui->widgetHour ? nValue : time.hour();
    int nMin = pWidget == ui->widgetMin ? nValue : time.minute();
    int nSec = pWidget == ui->widgetSec ? nValue : time.second();

    ui->timeEdit->setTime(QTime(nHour, nMin, nSec));
}

QString DateTime::datetime()
{
    QString time = QString("%1 %2")
            .arg( ui->dateEdit->date().toString("yyyy-MM-dd"))
            .arg(ui->timeEdit->time().toString("hh:mm:ss"));

    return time;
}

void DateTime::setDateTime(const QString &time)
{
    QDateTime datetime = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    ui->dateEdit->setDate(datetime.date());
    ui->calendarWidget->setSelectedDate(datetime.date());
    ui->dateEdit->setTime(datetime.time());
}
