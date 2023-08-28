#include "mask_widget.h"
#include "ui_mask_widget.h"

MaskWidget * MaskWidget::m_pSelf = Q_NULLPTR;

MaskWidget * MaskWidget::instance()
{
    if (m_pSelf == Q_NULLPTR)
    {
        m_pSelf = new MaskWidget;
    }
    return m_pSelf;
}


MaskWidget::MaskWidget(QWidget *parent) : QDialog(parent), ui(new Ui::MaskWidget)
{
    ui->setupUi(this);
    hide();
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |  Qt::WindowDoesNotAcceptFocus);
    qApp->installEventFilter(this);
}

MaskWidget::~MaskWidget()
{
    delete ui;
}

void MaskWidget::setMainWidget(QWidget *pWidget)
{
    this->resize(pWidget->size());
    this->setParent(pWidget);
    this->move(pWidget->x(), pWidget->y());
    m_pMainWidget = pWidget;
}

void MaskWidget::setNames(const QStringList& names)
{
     if(m_listName == names)
     {
         return;
     }
     m_listName = names;
 }

QStringList MaskWidget::names() const
{
 return m_listName;
}

bool MaskWidget::eventFilter(QObject *obj, QEvent *event)
{
 if(event->type() == QEvent::Hide)
 {
     if(m_listName.contains(obj->objectName()))
     {
         hide();
     }
     return QObject::eventFilter(obj, event);
 }

 if (event->type() == QEvent::Show)
 {
     if (!m_listName.contains(obj->objectName()))
     {
         return QObject::eventFilter(obj, event);
     }

     if(Q_NULLPTR == m_pMainWidget)
     {
         return QObject::eventFilter(obj, event);
     }

     resize(m_pMainWidget->size());
     show();

     auto pWidget = dynamic_cast<QWidget*>(obj);     //将object转换为普通QWidget
     if (Q_NULLPTR == pWidget)
     {
         return QObject::eventFilter(obj, event);
     }

     pWidget->activateWindow();
     pWidget->setFocus(Qt::ActiveWindowFocusReason);
     stackUnder(pWidget);    //将该窗口设置放到弹窗的下面

     m_pMainWidget->stackUnder(this);    //将主窗口设置放到该组件界面下方，就能够有一个比较清晰的层次关系

     //下面是实现将弹窗的位置移动到主程序的正中间，在这边实现的目的是为了减少代码量，毕竟写代码能偷的懒还是一定要偷的
     QRect screenGeometry = m_pMainWidget->geometry();
     int x = screenGeometry.x() + (screenGeometry.width() - pWidget->width()) / 2;
     int y = screenGeometry.y() + (screenGeometry.height() - pWidget->height()) / 2;
     pWidget->move(x, y);
 }

 return QObject::eventFilter(obj, event);
}
