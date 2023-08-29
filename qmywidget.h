#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QTextEdit>
#include <QPixmap>
#include "qmylabel.h"
#include "qmybutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "dbwidget.h"

#include <QTcpSocket>


class QMyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QMyWidget(QString str_name_, int tempid_, QWidget *parent);
    QMylabel *label_info;
    QLabel *label_pic;
    QString str_name;
    int tempid;
    void setInfo(QString str_info);

    QTcpSocket *tcpSocket;
    int pno,dno;

signals:
    void quit();
private:

};

#endif // QMYWIDGET_H
