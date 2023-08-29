#ifndef DBWIDGET_H
#define DBWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>


#include <QDebug>



#include <QFileDialog>

#include <QTcpSocket>
#include <QFile>


#include "message.h"
#include "entereventfilter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class dbWidget; }
QT_END_NAMESPACE

class dbWidget : public QWidget
{
    Q_OBJECT

public:
    dbWidget(QWidget *parent = nullptr);
    ~dbWidget();

    QTcpSocket *tcpSocket;
    int pno,dno;
    QString author;

    QWidget *chatWidget;

    void showMessage(message *m);
    void reLoad();

private:
    Ui::dbWidget *ui;
    QVBoxLayout *chatLayout;
    QFile *file;
    void sendData();

private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonImg_clicked();



};
#endif // DBWIDGET_H
