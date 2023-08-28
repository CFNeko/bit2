#ifndef PRESCRIPTIONINQUIRY_H
#define PRESCRIPTIONINQUIRY_H

#include <QWidget>
#include <QApplication>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QResizeEvent>

namespace Ui {
class PrescriptionInquiry;
}

class PrescriptionInquiry : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionInquiry(QWidget *parent = nullptr);
    ~PrescriptionInquiry();

    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();



private:
    Ui::PrescriptionInquiry *ui;
signals:
    void preToHome();
};

class ScrollAreaEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit ScrollAreaEventFilter(QScrollArea* scrollArea, QVBoxLayout* layout, QObject* parent = nullptr)
        : QObject(parent), scrollArea(scrollArea), layout(layout)
    {
        scrollArea->viewport()->installEventFilter(this);
    }

    bool eventFilter(QObject* watched, QEvent* event) override
    {
        if (watched == scrollArea->viewport() && event->type() == QEvent::Resize) {
            QResizeEvent* resizeEvent = static_cast<QResizeEvent*>(event);
            adjustScrollArea(resizeEvent->size().width());
        }
        return QObject::eventFilter(watched, event);
    }

private:
    void adjustScrollArea(int viewportWidth)
    {
        int totalButtonWidth = 0;
        for (int i = 0; i < layout->count(); ++i) {
            QWidget* widget = layout->itemAt(i)->widget();
            if (widget && widget->isVisible()) {
                totalButtonWidth += widget->width();
            }
        }

        bool showHorizontalScrollBar = totalButtonWidth > viewportWidth;
        scrollArea->setHorizontalScrollBarPolicy(showHorizontalScrollBar ? Qt::ScrollBarAsNeeded : Qt::ScrollBarAlwaysOff);
    }

    QScrollArea* scrollArea;
    QVBoxLayout* layout;
};
#endif // PRESCRIPTIONINQUIRY_H
