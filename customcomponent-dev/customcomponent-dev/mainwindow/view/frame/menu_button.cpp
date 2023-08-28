#include "menu_button.h"
#include<Qdebug>

MenuButton::MenuButton(QWidget* parent) : QPushButton(parent)
{

}

MenuButton::MenuButton(int id, QWidget* parent) : QPushButton(parent), m_nId(id)
{

}

MenuButton::~MenuButton()
{

}

void MenuButton::mousePressEvent(QMouseEvent *e)
{

}

void MenuButton::mouseReleaseEvent(QMouseEvent *e)
{
    btnClick();
}

int MenuButton::id() const
{
    return m_nId;
}

void MenuButton::setId(const int& id)
{
    m_nId = id;
}

QVariant MenuButton::data() const
{
    return m_data;
}

void MenuButton::setData(const QVariant &data)
{
    m_data = data;
}

void MenuButton::btnClick()
{
    bool change = true;
    emit signal_btnClicked(text(), id(), change);

    if(change)
    {
        click();
    }
}

