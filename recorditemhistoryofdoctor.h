#ifndef RECORDITEMHISTORYOFDOCTOR_H
#define RECORDITEMHISTORYOFDOCTOR_H

#include <QWidget>
#include <QMouseEvent>
#include"listtemplate.h"
#include<QLineEdit>
#include<QComboBox>
#include<QTextEdit>
#include <QSqlDatabase>
#include <QPainter>
#include <QScrollArea>
#include "doctorpage.h"
#include "userfriendlyitems.h"
#include <QEvent>

namespace Ui {
class RecordItemHistoryofDoctor;
}

class RecordItemHistoryofDoctor : public QWidget
{
    Q_OBJECT

public:
    explicit RecordItemHistoryofDoctor(QWidget *parent = nullptr);
    ~RecordItemHistoryofDoctor();
    void paintEvent(QPaintEvent*);

private:
    Ui::RecordItemHistoryofDoctor *ui;
};

#endif // RECORDITEMHISTORYOFDOCTOR_H
