#include "MessageCenter.h"
#include "ui_messagecenter.h"
#include "ui_msgitem.h"
#include <QListWidgetItem>
#include <QDesktopWidget>


MsgItem::MsgItem(QWidget *parent) : QWidget(parent), ui(new Ui::MsgItem)
{
    ui->setupUi(this);
    ui->btnDelete->setVisible(false);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MsgItem::on_btnDeleteClicked);
}
MsgItem::~MsgItem()
{
    delete ui;
}

QString MsgItem::errorText() const
{
    return ui->lbMsg->text();
}

void MsgItem::setErrorText(const QString& text)
{
    ui->lbMsg->setText(text);
}

ErrorStatus MsgItem::errorStatus() const
{
    return m_eErrorStatus;
}

void MsgItem::setErrorStatus(const ErrorStatus& eStatus)
{
    m_eErrorStatus = eStatus;
    QString strProperty = eStatus == NOT_READ ? "notread" : "haveread";
    ui->lbIndex->setProperty("labeltype", strProperty);
    this->style()->unpolish(ui->lbIndex);
    this->style()->polish(ui->lbIndex);
}

ErrorInfo MsgItem::errorInfo() const
{
    return m_errInfo;
}

void MsgItem::setErrorInfo(const ErrorInfo& listInfo)
{
    m_errInfo = listInfo;
}

int MsgItem::msgId() const
{
    return m_nMsgId;
}

void MsgItem::setMsgId(const int& msgId)
{
    m_nMsgId = msgId;
}

bool MsgItem::cleanBtnVisible() const
{
    return m_bVisible;
}

void MsgItem::setcleanBtnVisible(const bool& visible)
{
    m_bVisible = visible;
}

void MsgItem::selected(bool bSelected)
{
    setStyleSheet(bSelected ? "background-color:#D7E2EA" : "background-color:#E7ECEF");
    setDeleted(bSelected && m_errInfo.deleted);
}

void MsgItem::setDeleted(bool deleted)
{
    ui->btnDelete->setVisible(deleted);
}

void MsgItem::on_btnDeleteClicked()
{
    emit signal_delete();
}

MessageCenter * MessageCenter::m_pSelf = Q_NULLPTR;
MessageCenter* MessageCenter::Instance()
{
    if (!m_pSelf)
    {
        m_pSelf = new MessageCenter;
    }
    return m_pSelf;
}
void MessageCenter::Release()
{
    if (m_pSelf != Q_NULLPTR)
    {
        delete m_pSelf;
        m_pSelf = Q_NULLPTR;
    }
}

MessageCenter::MessageCenter(QWidget *parent) : QWidget(parent), ui(new Ui::MessageCenter)
{
    ui->setupUi(this);
    initPage();
}

MessageCenter::~MessageCenter()
{
    delete ui;
}

void MessageCenter::initPage()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground, true);
    ui->widgetInfo->setVisible(false);
    connect(ui->btnClose, &QPushButton::clicked, this, &MessageCenter::on_btnCloseClicked);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MessageCenter::on_listItemClicked);
}

void MessageCenter::resetPage()
{
    ui->lbDetails->clear();
    ui->lbCode->clear();
    ui->lbSolution->clear();
    ui->lbDateTime->clear();
}

void MessageCenter::showEvent(QShowEvent*)
{
    QRect rect = QApplication::desktop()->availableGeometry();
    move(rect.width() - this->size().width() - 1, rect.height() - this->size().height() - 1);
}

void MessageCenter::on_btnCloseClicked()
{
    close();
}

void MessageCenter::on_listItemClicked(QListWidgetItem* pItem)
{
    if (!ui->widgetInfo->isVisible())
    {
        ui->widgetInfo->setVisible(true);
    }
    int nIndex = ui->listWidget->currentRow();
    if (nIndex < 0)
    {
        return;
    }
    if (m_pCurrentItem == Q_NULLPTR)
    {
        m_pCurrentItem = pItem;
        auto pError = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
        if (pError == Q_NULLPTR)
        {
            return;
        }
        pError->setErrorStatus(HAVE_READ);
        pError->selected(true);
        this->errorItemInfo(pError);
        return;
    }
    auto* pError = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(m_pCurrentItem));
    if (pError == Q_NULLPTR)
    {
        return;
    }
    pError->selected(false);
    m_pCurrentItem = pItem;
    pError = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
    if (pError == Q_NULLPTR)
    {
        return;
    }
    pError->setErrorStatus(HAVE_READ);
    pError->selected(true);
    this->errorItemInfo(pError);
}

void MessageCenter::errorItemInfo(MsgItem *pWidget)
{
    ErrorInfo info = pWidget->errorInfo();
    ui->lbCode->setText(tr("0X0%1").arg(info.code));
    ui->lbDetails->setText(tr("%1").arg(info.info));
    ui->lbSolution->setText(tr("%1").arg(info.solution));
    ui->lbDateTime->setText(info.time.toString("yyyy-MM-dd hh:mm:ss"));
}

void MessageCenter::slot_delete()
{
    auto pError = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(ui->listWidget->currentItem()));
    if (pError == Q_NULLPTR)
    {
        return;
    }
    closeError(pError->msgId());
}

int MessageCenter::pushError(const QString& strErrorName, const ErrorInfo& errInfo, bool isStick)
{
    auto pError = new MsgItem(this);
    pError->setErrorText(strErrorName);
    pError->setErrorInfo(errInfo);
    pError->setErrorStatus(NOT_READ);
    pError->setcleanBtnVisible(errInfo.deleted);
    pError->setMsgId(++m_nMsgId);

    auto pItem = new QListWidgetItem(ui->listWidget);
    pItem->setSizeHint(QSize(196, 40));

    //消息置顶
    if (isStick)
    {
        ui->listWidget->insertItem(1, pItem);
    }
    else
    {
        ui->listWidget->addItem(pItem);
    }
    ui->listWidget->setItemWidget(pItem, pError);
    m_mError.insert(m_nMsgId, pItem);
    emit signal_errorCount(ui->listWidget->count());
    if (!isVisible())
    {
        show();
    }
    if (errInfo.deleted)
    {
        connect(pError, &MsgItem::signal_delete, this, &MessageCenter::slot_delete);
    }
    return m_nMsgId;
}

void MessageCenter::closeError(int nMsgId)
{
    QListWidgetItem* pError = m_mError.value(nMsgId);
    if (m_pCurrentItem == pError)
    {
        m_pCurrentItem = Q_NULLPTR;
    }
    QListWidgetItem *pItem = ui->listWidget->takeItem(ui->listWidget->row(pError));
    m_mError.remove(nMsgId);
    resetPage();
    delete pItem;
    pItem = Q_NULLPTR;
    if (m_mError.isEmpty())	//如果错误消息为空，则隐藏界面
    {
        hide();
        ui->widgetInfo->setVisible(false);
    }
    emit signal_errorCount(ui->listWidget->count());
}
