#include "tablewidget.h"
#include "ui_listwidgetitem.h"
#include <QDebug>


static QMap<QString, bool> m_mSelected;
TableWidget::TableWidget(QWidget *parent) : QTableWidget(parent), m_pCellPos(0, 0)
{
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);

    this->setColumnCount(5);
    this->setColumnWidth(0, 56);
    this->setColumnWidth(1, 56);
    this->setColumnWidth(2, 56);
    this->setColumnWidth(3, 56);
    this->setColumnWidth(4, 55);

    this->setFocusPolicy(Qt::NoFocus);
}
TableWidget::~TableWidget() = default;

void TableWidget::initTable(const QVariantList& picList)
{
    this->setRowCount(picList.size() % 5 == 0 ? picList.size() / 5 : picList.size() / 5 + 1);

    if (picList.isEmpty())
    {
        return;
    }

    for (const auto& pic : picList)
    {
        auto pWidget = new QWidget(this);
        pWidget->setFixedSize(QSize(56, 56));
        pWidget->setProperty("widgettype", "transparent");
        auto pLayout = new QHBoxLayout();
        pLayout->setMargin(0);
        pLayout->setSizeConstraint(QLayout::SetMinimumSize);

        pWidget->setLayout(pLayout);
        auto pBtn = new QPushButton;
        pBtn->setFlat(true);
        pBtn->setIcon(QIcon(m_iconPath + pic.toString()));
        pBtn->setProperty("buttontype", "selecticon");
        connect(pBtn, &QPushButton::clicked, this, &TableWidget::on_itemBtnClicked);

        pLayout->addWidget(pBtn);
        m_mBtn.insert(pic.toString(), pBtn);

        this->setCellWidget(m_pCellPos.x(), m_pCellPos.y(), pWidget);
        int nColumn = m_pCellPos.y();
        int nRow = m_pCellPos.x();
        if (++nColumn == 5)
        {
            m_pCellPos = QPoint(++nRow, 0);
            continue;
        }
        m_pCellPos = QPoint(nRow, nColumn);
        this->setRowHeight(nRow, 56);
    }
}

void TableWidget::showEvent(QShowEvent *event)
{
    for (auto& btn : m_mBtn.keys())
    {
        if (m_mSelected.contains(btn))
        {
            m_mBtn[btn]->setDisabled(m_mSelected[btn]);
        }
    }
}

void TableWidget::on_itemBtnClicked()
{
    auto pBtn = qobject_cast<QPushButton *>(QObject::sender());
    if (Q_NULLPTR == pBtn)
    {
        return;
    }
    emit signal_currentIcon(m_mBtn.key(pBtn));

    pBtn->setDisabled(true);
    if (!m_selectedBtn.isEmpty())
    {
        m_mSelected.remove(m_selectedBtn);
        m_mBtn[m_selectedBtn]->setDisabled(false);
    }

    m_selectedBtn = m_mBtn.key(pBtn);
    m_mSelected[m_selectedBtn] = true;
}

void TableWidget::setBtnDisabled(const QString& name)
{
    if (Q_NULLPTR == m_mBtn[name])
    {
        return;
    }
    m_mBtn[name]->click();
}

QString TableWidget::path() const
{
    return m_iconPath;
}

void TableWidget::setPath(const QString &path)
{
    m_iconPath = path;
}
