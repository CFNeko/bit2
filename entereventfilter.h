#ifndef ENTEREVENTFILTER_H
#define ENTEREVENTFILTER_H

#include <QObject>
#include <QKeyEvent>

class EnterEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit EnterEventFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
signals:
    void enter();

};

#endif // ENTEREVENTFILTER_H
