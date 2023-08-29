#ifndef HEALTHEVALUATION_H
#define HEALTHEVALUATION_H

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>

#include "userfriendlyitems.h"

namespace Ui {
class HealthEvaluation;
}

class HealthEvaluation : public QWidget
{
    Q_OBJECT

public:
    explicit HealthEvaluation(QWidget *parent = nullptr);
    ~HealthEvaluation();
    void paintEvent(QPaintEvent *) override;
private:
    Ui::HealthEvaluation *ui;
    int CalculateStrechScore(QString sex);
    int CalculateBalanceScore(QString sex);
    int CalculateReactScore(QString sex);
    double CalculateBMI(double height, double weight);
    void CalculateTotalScore(int OScore, double BMI, int strechScore, int balanceScore, int reactScore);
    double weight = 87;
    double height_ = 1.95;
    int OScore;
signals:
    void hClosed();
protected:
    void closeEvent(QCloseEvent *event) override {
        emit hClosed();
        QWidget::closeEvent(event);
    }
};

#endif // HEALTHEVALUATION_H
