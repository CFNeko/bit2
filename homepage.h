#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QMouseEvent>
#include"listtemplate.h"
#include<QLineEdit>
#include<QComboBox>
#include<QTextEdit>
#include"prescriptioninquiry.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();
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



private slots:
        void on_prescription_inquiry_clicked();
        void on_PreToHome_Received();

        void on_pushButton_modify_clicked();

        void on_pushButton_submit_clicked();

private:
    Ui::HomePage *ui;
    ListTemplate* m_pListTemplate;
     PrescriptionInquiry* prescription_inquiry;

};

#endif // HOMEPAGE_H
