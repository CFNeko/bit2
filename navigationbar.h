#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>

namespace Ui {
class NavigationBar;
}

class NavigationBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar();

private:
    Ui::NavigationBar *ui;
};

#endif // NAVIGATIONBAR_H
