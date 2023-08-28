#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>

class MenuButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId DESIGNABLE true)
    Q_PROPERTY(QVariant data READ data WRITE setData DESIGNABLE true)
public:
    explicit MenuButton(QWidget *parent = 0);
    explicit MenuButton(int id, QWidget *parent = 0);
    ~MenuButton();


    int id() const;
    void setId(const int& id);

    QVariant data() const;
    void setData(const QVariant& data);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
    void signal_btnClicked(const QString&, int, bool& change);   //按钮被按下，需要检测当前界面是否有,返回值change标志是否切换

private:
    void btnClick();

    int m_nId{ -1 };
    QVariant m_data{ QVariant() };
};

#endif // MENUBUTTON_H
