#ifndef COLOR_WIDGET_H
#define COLOR_WIDGET_H

#include <QWidget>
#include <QShowEvent>
namespace Ui {
class ColorWidget;
}

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = nullptr);
    ~ColorWidget();

private:
    void initPage();
    void updateColor(const QColor& color);

private:
    Ui::ColorWidget *ui;
};

#endif // COLOR_WIDGET_H
