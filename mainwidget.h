#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QTextEdit>
#include <QtWidgets>
#include <QPushButton>
#include <QString>
#include <QDate>
#include <QLabel>
#include <QPixmap>
#include "qmywidget.h"
#include <QTabWidget>

#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class mainWidget; }
QT_END_NAMESPACE

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

    QTcpSocket *tcpSocket;
    int pno;


private:
    Ui::mainWidget *ui;

signals:
    void mClosed();
    void chat();
};
#endif // MAINWIDGET_H
