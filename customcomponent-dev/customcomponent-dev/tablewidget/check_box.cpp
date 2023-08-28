#include "check_box.h"

CheckBox::CheckBox(QString text, QWidget *parent) : QCheckBox(parent)
{
    setText(text);
}

CheckBox::~CheckBox()
{

}

void CheckBox::mouseReleaseEvent(QMouseEvent *e)
{
    btnClick();
}

QVariant CheckBox::data() const
{
    return m_data;
}

void CheckBox::setData(const QVariant &data)
{
    m_data = data;
}

void CheckBox::btnClick()
{
    if (checkState() == Qt::Unchecked)
    {
        setCheckState(Qt::PartiallyChecked);
    }
    click();
}
