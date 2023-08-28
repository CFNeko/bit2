#ifndef NAVIGATIONDESIGN_H
#define NAVIGATIONDESIGN_H

#include <QWidget>

namespace Ui {
class navigationDesign;
}

class navigationDesign : public QWidget
{
    Q_OBJECT

public:
    explicit navigationDesign(QWidget *parent = nullptr);
    ~navigationDesign();


private:
    Ui::navigationDesign *ui;
};

#endif // NAVIGATIONDESIGN_H
