#ifndef MessageCenter_H
#define MessageCenter_H

#include <QWidget>
#include <QDatetime>
#include <QMap>

class QListWidgetItem;

enum SystemErrorType{
    SYSTEM_INIT = 0,
    SERVICE_DISCONNECT
};

enum ErrorStatus{
    NOT_READ = 0,
    HAVE_READ
};

struct ErrorInfo
{
    SystemErrorType code;
    QString info;
    QString solution;
    QDateTime time;
    bool deleted;
    ErrorInfo() : code(SYSTEM_INIT), info(), solution(), time(QDateTime::currentDateTime()), deleted(false)
    {

    }
};

namespace Ui {
class MsgItem;
}

class MsgItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString errorText READ errorText WRITE setErrorText DESIGNABLE true)
    Q_PROPERTY(ErrorStatus errorStatus READ errorStatus WRITE setErrorStatus DESIGNABLE true)
    Q_PROPERTY(ErrorInfo errorInfo READ errorInfo WRITE setErrorInfo DESIGNABLE true)
    Q_PROPERTY(int msgId READ msgId WRITE setMsgId DESIGNABLE true)

public:
    explicit MsgItem(QWidget *parent = Q_NULLPTR);
    ~MsgItem();

    QString errorText() const;
    void setErrorText(const QString& text);

    ErrorStatus errorStatus() const;
    void setErrorStatus(const ErrorStatus& eStatus);

    ErrorInfo errorInfo() const;
    void setErrorInfo(const ErrorInfo& listInfo);

    int msgId() const;
    void setMsgId(const int& msgId);

    bool cleanBtnVisible() const;
    void setcleanBtnVisible(const bool& visible);

    void setDeleted(bool deleted);
    void selected(bool bSelected);
private slots:
    void on_btnDeleteClicked();

signals:
    void signal_delete();
private:
    Ui::MsgItem* ui;
    ErrorStatus m_eErrorStatus{NOT_READ};
    ErrorInfo m_errInfo;
    int m_nMsgId{ 0 };
    bool m_bVisible{};
};

namespace Ui {
class MessageCenter;
}

class MessageCenter : public QWidget
{
    Q_OBJECT

public:

    static MessageCenter*  Instance();	    //获取单实例
    static void             Release();		//释放单实例;

    int pushError(const QString& strErrorName, const ErrorInfo& errInfo, bool isStick = false);
    void closeError(int nMsgId);

protected:

    void showEvent(QShowEvent*) override;

private:
    explicit MessageCenter(QWidget *parent = 0);
    ~MessageCenter();

    void initPage();
    void resetPage();

    void errorItemInfo(MsgItem* pWidget);

private slots:
    void on_btnCloseClicked();
    void on_listItemClicked(QListWidgetItem* pItem);
    void slot_delete();
signals:
    void signal_errorCount(int nCount);
private:
    Ui::MessageCenter *ui;

    static MessageCenter* m_pSelf;
    QMap<int, QListWidgetItem*>	m_mError;
    QListWidgetItem* m_pCurrentItem{Q_NULLPTR};
    int     m_nMsgId{0};
};

#endif // MessageCenter_H
