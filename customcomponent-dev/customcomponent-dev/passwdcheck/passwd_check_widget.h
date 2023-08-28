#ifndef PASSWD_CHECK_WIDGET_H
#define PASSWD_CHECK_WIDGET_H

#include <QWidget>

namespace Ui {
class PasswdCheckWidget;
}

enum PasswordModel
{
    LEVEL,
    PROMPT
};

class PasswdCheckWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString passwd READ passwd WRITE setPassWd DESIGNABLE true)
    Q_PROPERTY(QString cpasswd READ cpasswd WRITE setCPasswd DESIGNABLE true)
public:
    explicit PasswdCheckWidget(QWidget *parent = 0);
    ~PasswdCheckWidget();

    QString passwd() const
    {
        return m_passWd;
    }
    void setPassWd(const QString& passwd)
    {
        m_passWd = passwd;
    }

    QString cpasswd() const
    {
        return m_cpassWd;
    }
    void setCPasswd(const QString& cpasswd)
    {
        m_cpassWd = cpasswd;
    }

    bool checkPasswdStrength();

    bool checkPasswd();

    void setPrompt(bool checked);

    void setModel(PasswordModel model);

private:
    enum PasswordSafeLevel
    {
        Weak,
        Medium,
        Strong
    };
private:
    void setPasswdLevel(PasswordSafeLevel level);

private:

    Ui::PasswdCheckWidget *ui;

    QRegExp m_regStrong;
    QRegExp m_regMedium;
    QRegExp m_regWeak;
    QString m_passWd{ QString() };
    QString m_cpassWd{ QString() };
};

#endif // PASSWD_CHECK_WIDGET_H
