#ifndef PATIENTCHATWIDGET_H
#define PATIENTCHATWIDGET_H

#include <QWidget>
#include "dbwidget.h"

#include <QTcpSocket>
#include <QTimer>
#include <QDateTime>
#include <QHostAddress>

#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class patientChatWidget; }
QT_END_NAMESPACE

class patientChatWidget : public QWidget
{
    Q_OBJECT

public:
    patientChatWidget(QWidget *parent = nullptr);
    ~patientChatWidget();

private:
    Ui::patientChatWidget *ui;

    QTcpSocket *tcpSocket;

    int pno;
    int dno;
    QString author;

    QMediaPlayer* player;

    bool imageMode;
    QByteArray *imgData;
    QStringList imgHead;

private slots:
    void on_tcpSocket_readyRead();
    void on_doctor1234_clicked();
    void on_doctor5678_clicked();
};
#endif // PATIENTCHATWIDGET_H
