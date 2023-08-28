#include "passwd_check_widget.h"
#include "ui_passwd_check_widget.h"

PasswdCheckWidget::PasswdCheckWidget(QWidget *parent) : QWidget(parent), ui(new Ui::PasswdCheckWidget)
{
    ui->setupUi(this);
    m_regStrong.setPattern(QString("(?=^.{8,16}$)((?=.*\\d)|(?=.*\\W+))(?![.\\n])(?=.*[A-Z])(?=.*[a-z]).*$"));
    m_regMedium.setPattern(QString("(?!^\\d+$)(?!^[a-zA-Z]+$).{8,}"));
    m_regWeak.setPattern(QString("(?!^\\d+$)(?!^[a-zA-Z]+$).{6,}"));
}

PasswdCheckWidget::~PasswdCheckWidget()
{
    delete ui;
}

void PasswdCheckWidget::setModel(PasswordModel model)
{
    ui->stackedWidget->setCurrentIndex(model);
}

void PasswdCheckWidget::setPrompt(bool checked)
{
    QString prompt = checked ? QString("At least 6 digits.\nMust contain both number and character.")
                             : QString("The two passwords are not the same.\nPlease try again.");

    QString property = checked ? QString("passwdprompt") : QString("passwdpromptwarning");

    ui->txtTips->setText(prompt);

    ui->txtTips->setProperty("labeltype", property);

    this->style()->unpolish(ui->txtTips);
    this->style()->polish(ui->txtTips);
    if(!isVisible())
    {
        setVisible(true);
    }
}

bool PasswdCheckWidget::checkPasswd()
{
    if(m_passWd != m_cpassWd)
    {
        return false;
    }
    return true;
}

bool PasswdCheckWidget::checkPasswdStrength()
{
    if(m_regStrong.exactMatch(m_passWd))
    {
        setPasswdLevel(Strong);
        return true;
    }
    if(m_regMedium.exactMatch(m_passWd))
    {
        setPasswdLevel(Medium);
        return true;
    }
    if(m_regWeak.exactMatch(m_passWd))
    {
        setPasswdLevel(Weak);
        return true;
    }
    setVisible(false);
    return false;
}

void PasswdCheckWidget::setPasswdLevel(PasswordSafeLevel level)
{
    switch (level) {
    case Weak:
    {
        ui->progressBar->setValue(33);
        ui->lbIntensity->setText("Weak");
        ui->progressBar->setProperty("level", "weak");
        ui->lbIntensity->setProperty("labeltype", "passwdlevelweak");
        break;
    }
    case Medium:
    {
        ui->progressBar->setValue(66);
        ui->lbIntensity->setText("Medium");
        ui->progressBar->setProperty("level", "medium");
        ui->lbIntensity->setProperty("labeltype", "passwdlevelmedium");
        break;
    }
    case Strong:
    {
        ui->progressBar->setValue(100);
        ui->lbIntensity->setText("Strong");
        ui->progressBar->setProperty("level", "strong");
        ui->lbIntensity->setProperty("labeltype", "passwdlevelstrong");
        break;
    }
    default:
        break;
    }

    this->style()->unpolish(ui->progressBar);
    this->style()->polish(ui->progressBar);
    this->style()->unpolish(ui->lbIntensity);
    this->style()->polish(ui->lbIntensity);

    if(!isVisible())
    {
        setVisible(true);
    }
}
