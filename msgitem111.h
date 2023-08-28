#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class MsgItem;
}

class MsgItem : public QWidget
{    Q_OBJECT
     //可按照下面的方法自己添加需要的功能
     Q_PROPERTY(QString msg READ msg WRITE setMsg DESIGNABLE true)
     Q_PROPERTY(QString header READ header WRITE setHeader DESIGNABLE true)
     Q_PROPERTY(QString name READ name WRITE setName DESIGNABLE true)
     Q_PROPERTY(QString uuid READ uuid WRITE setUuid DESIGNABLE true)
     Q_PROPERTY(QString datetime READ datetime WRITE setDatetime DESIGNABLE true)
     Q_PROPERTY(int count READ count WRITE setCount DESIGNABLE true)

public:
    explicit MsgItem(QWidget *parent = 0);
     ~MsgItem();

    QString msg() const;
    void setMsg(const QString& msg);

    QString header() const;
    void setHeader(const QString& header);

    QString uuid() const
    {
        return m_uuid;
    }
    void setUuid(const QString& uuid)
    {
        m_uuid = uuid;
    }

    QString name() const;
    void setName(const QString& name);

    QString datetime() const;
    void setDatetime(const QString& datetime);

    int count() const;
    void setCount(const int count);

    void setData( const QString &msg,
                        const QString& nick,
                        const QString& header,
                        const QString& name,
                        const QString& time );

    void selected(bool selected);

protected:
     virtual void mousePressEvent( QMouseEvent *event );


private slots:
     void on_btnDeleteClicked();

signals:
     void signal_selected(MsgItem*);
     void signal_delete(QWidget*);

private:
     Ui::MsgItem *ui;
     QString m_header{""};
     QString m_uuid{""};
};


#endif // LISTTEMPLATE_H
