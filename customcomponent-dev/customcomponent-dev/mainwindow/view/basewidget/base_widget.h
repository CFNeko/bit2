#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);
    virtual bool saveRequest();

};

#endif // BASE_WIDGET_H
