#include "healthevaluation.h"
#include "ui_healthevaluation.h"

HealthEvaluation::HealthEvaluation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthEvaluation),
    OScore(4)
{
    ui->setupUi(this);

    ui->linkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->linkLabel->setOpenExternalLinks(true); // 在默认浏览器中打开链接
    ui->BMIValue->setText(QString::number(CalculateBMI(height_, weight)));
    RoundedRectButton *submit = new RoundedRectButton;
    submit->setText("提交");
    QHBoxLayout *submitlayout = new QHBoxLayout;
    submitlayout->addStretch(1);

    submitlayout->addWidget(submit);
    submitlayout->setStretchFactor(submit, 1);

    submitlayout->addStretch(1);

    ui->pagelayout->addLayout(submitlayout);

    ui->pagelayout->setStretch(0, 3);
    ui->pagelayout->setStretch(1, 2);
    ui->pagelayout->setStretch(2, 2);
    ui->pagelayout->setStretch(3, 2);
    ui->pagelayout->setStretch(4, 2);
    ui->pagelayout->setStretch(5, 2);
    ui->pagelayout->setStretch(6, 1);

    this->setLayout(ui->pagelayout);
    connect(ui->score1, &QRadioButton::clicked, this, [&]{OScore = 1;});
    connect(ui->score2, &QRadioButton::clicked, this, [&]{OScore = 2;});
    connect(ui->score3, &QRadioButton::clicked, this, [&]{OScore = 3;});
    connect(ui->score4, &QRadioButton::clicked, this, [&]{OScore = 4;});
    connect(ui->score5, &QRadioButton::clicked, this, [&]{OScore = 5;});


    connect(submit, &QPushButton::clicked, this, [=]
    {
        //        api函数：判断男女，传体重（kg），身高（m）
        QString sex = "男";
        if(sex == "男"){
            CalculateTotalScore(OScore, CalculateBMI(height_, weight), CalculateStrechScore(sex), CalculateBalanceScore(sex), CalculateReactScore(sex));
        }else{
            CalculateTotalScore(OScore, CalculateBMI(height_, weight), CalculateStrechScore(sex), CalculateBalanceScore(sex), CalculateReactScore(sex));
        }
    });

}

HealthEvaluation::~HealthEvaluation()
{
    delete ui;
}

int HealthEvaluation::CalculateStrechScore(QString sex)
{
    if(sex == "男"){
        if(ui->strechValue->text().toDouble() > 20){
            return 5;
        }else if(ui->strechValue->text().toDouble() >14){
            return 4;
        }else if(ui->strechValue->text().toDouble() >9){
            return 3;
        }else if(ui->strechValue->text().toDouble() > 2){
            return 2;
        }else {
            return 1;
        }
    }
    else{
        if(ui->strechValue->text().toDouble() > 20){
            return 5;
        }else if(ui->strechValue->text().toDouble() >14){
            return 4;
        }else if(ui->strechValue->text().toDouble() >8){
            return 3;
        }else if(ui->strechValue->text().toDouble() > 2){
            return 2;
        }else {
            return 1;
        }
    }
}

int HealthEvaluation::CalculateBalanceScore(QString sex)
{
    if(sex == "男"){
        if(ui->balanceValue->text().toDouble() > 98){
            return 5;
        }else if(ui->balanceValue->text().toDouble() >42){
            return 4;
        }else if(ui->balanceValue->text().toDouble() >18){
            return 3;
        }else if(ui->balanceValue->text().toDouble() > 6){
            return 2;
        }else {
            return 1;
        }
    }
    else{
        if(ui->balanceValue->text().toDouble() > 90){
            return 5;
        }else if(ui->balanceValue->text().toDouble() >34){
            return 4;
        }else if(ui->balanceValue->text().toDouble() >16){
            return 3;
        }else if(ui->balanceValue->text().toDouble() > 6){
            return 2;
        }else {
            return 1;
        }
    }
}

int HealthEvaluation::CalculateReactScore(QString sex)
{
    if(sex == "男"){
        if(ui->reactValue->text().toDouble() > 0.61){
            return 1;
        }else if(ui->reactValue->text().toDouble() >0.50){
            return 2;
        }else if(ui->reactValue->text().toDouble() >0.44){
            return 3;
        }else if(ui->reactValue->text().toDouble() > 0.39){
            return 4;
        }else {
            return 5;
        }
    }
    else{
        if(ui->reactValue->text().toDouble() > 0.66){
            return 1;
        }else if(ui->reactValue->text().toDouble() >0.53){
            return 2;
        }else if(ui->reactValue->text().toDouble() >0.45){
            return 3;
        }else if(ui->reactValue->text().toDouble() > 0.40){
            return 4;
        }else {
            return 5;
        }
    }
}

double HealthEvaluation::CalculateBMI(double height, double weight)
{
    return weight /(height * height);
}

void HealthEvaluation::CalculateTotalScore(int OScore, double BMI, int strechScore, int balanceScore, int reactScore)
{
    double total = OScore * 8 +
            BMI * 4 +
            strechScore * 2 +
            balanceScore * 1 +
            reactScore * 1;
    total /= 1.5;
    if (total >= 85){
        QMessageBox::information(this, "您的健康评价", "恭喜您，您的健康状况为：优秀！");
    }else if (total >= 75){
        QMessageBox::information(this, "您的健康评价", "恭喜您，您的健康状况为：良好！");
    }else if (total >= 60){
        QMessageBox::information(this, "您的健康评价", "您的健康状况为：合格！请您加强锻炼！");
    }else{
        QMessageBox::information(this, "您的健康评价", "您的健康状况为：较差！请您加强锻炼！");
    }
    return;
}

    void HealthEvaluation::paintEvent(QPaintEvent *) {
        QPainter painter(this);
        QPixmap background(":/resource111/evaluation.png");  // 替换为你的图片路径
        painter.drawPixmap(0, 0, width(), height(), background);
    }
