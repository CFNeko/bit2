#include "entereventfilter.h"

EnterEventFilter::EnterEventFilter(QObject *parent) : QObject(parent)
{

}

bool EnterEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            emit enter();
            return true; // 拦截 Enter 键事件
        }
    }
    return QObject::eventFilter(obj, event);
}
