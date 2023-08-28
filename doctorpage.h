#ifndef DOCTORPAGE_H
#define DOCTORPAGE_H

#include <QWidget>
#include <QMouseEvent>
#include"listtemplate.h"
#include<QLineEdit>
#include<QComboBox>
#include<QTextEdit>
#include<QTextEdit>
#include<QDebug>
#include<QPainter>
#include "recorditemtable.h"
#include "prescriptiontable.h"
#include "recorditemhistoryofdoctor.h"
#include "registraitondoctorpage.h"

namespace Ui {
class DoctorPage;
}

class DoctorPage : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorPage(QWidget *parent = nullptr);
    ~DoctorPage();
    void addCustomWidget();
    //左侧部分的代码
        QLabel *UserNameLabel;
        QLabel *NameLabel;
        QLabel *SexLabel;
        QLabel *DepartmentLabel;
        QLabel *AgeLabel;
        QLabel *OtherLabel;
        QLineEdit *UserNameLineEdit;
        QLineEdit *NameLineEdit;
        QComboBox *SexComBox;
        QLineEdit *DepartmentEdit;
        QLineEdit *AgeEdit;
        QGridLayout *LeftLayout;
        //右侧部分的代码
        QLabel *HeadLabel;
        QLabel *HeadIconLabel;
        QPushButton *UpdateHeadButn;
        QHBoxLayout *TopRightLayout;
        QLabel *IntroductionLabel;
        QTextEdit *IntroductionText;
        QVBoxLayout *RightLayout;


        //底部部分
        QPushButton *OKBtn;
        QPushButton *CancelBtn;
        QHBoxLayout *BtnLayout;

        void paintEvent(QPaintEvent *);
private:
    Ui::DoctorPage *ui;
    ListTemplate* m_pListTemplate;

};

#endif // DOCTORPAGE_H
