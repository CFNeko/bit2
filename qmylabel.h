#ifndef QMYLABEL_H
#define QMYLABEL_H

#include <QWidget>
#include <QLabel>
class QMylabel : public QLabel
{
    Q_OBJECT
public:
    explicit QMylabel(QWidget *parent = nullptr);
    QLabel *label_text;
signals:

};

#endif // QMYLABEL_H
