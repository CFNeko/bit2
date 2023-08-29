#ifndef QMYBUTTON_H
#define QMYBUTTON_H

#include <QWidget>
#include <QPushButton>
class QMyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QMyButton(QWidget *parent = nullptr);

signals:

};

#endif // QMYBUTTON_H
