#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>
#include <QVariant>

class CheckBox : public QCheckBox
{
    Q_OBJECT

public:

    //using 关键字是在C++11之后出现的，有些版本是不支持的，所以这边我们不使用
    //using QCheckBox::QCheckBox;

    explicit CheckBox(QString text, QWidget* parent = nullptr);
    ~CheckBox();

    QVariant data() const;
    void setData(const QVariant& data);

protected:
    void mouseReleaseEvent(QMouseEvent* e);

private:
    void btnClick();

    QVariant m_data{ QVariant() };
};

#endif // CHECKBOX_H
