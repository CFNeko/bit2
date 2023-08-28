#include "base_widget.h"

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{

}

bool BaseWidget::saveRequest()
{
    return true;
}

//每个继承的子类均应该实现该函数，保证在application不重启切换语言
//bool BaseWidget::event(QEvent* ev)
//{
//    if (ev->type() == QEvent::LanguageChange)
//    {
//        ui->retranslateUi(this);
//    }
//    return QWidget::event(ev);
//}
