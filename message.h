#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class message;
}

class message : public QLabel
{
    Q_OBJECT

public:
    explicit message(QString str,QString time,QString author,QByteArray img,QString currentAuthor,QWidget *parent = nullptr);
    ~message();

private:
    Ui::message *ui;
    bool Ismine;

};

#endif // MESSAGE_H
