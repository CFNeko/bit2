#ifndef TITLE_BAR_WIDGET_H
#define TITLE_BAR_WIDGET_H

#include <QWidget>
#include <QMenu>
namespace Ui {
class TitleBarWidget;
}

class TitleBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBarWidget(QWidget *parent = 0);
    ~TitleBarWidget();

    void setCurrentUser(const QString& user);
    QString getCurrentUser()const;

    void setCurrentPage(const QString& page);

protected:
    bool event(QEvent *event) override;

private:
    void initPage();

private slots:
    void slot_menuClicked();
    void slot_userMenuClicked();

    void on_btnMinClicked();
    void on_btnMaxClicked();
    void on_btnCloseClicked();

signals:
    void signal_subMenuClicked(const QString&, int);
    void signal_nextsubMenuClicked(const QString&, int, bool&);
    void signal_menuClicked(const QString& action);

private:
    Ui::TitleBarWidget *ui;
    QAction* m_pCurrentUser{ Q_NULLPTR };
    QAction* m_pLockScreen{ Q_NULLPTR };
    QAction* m_pQuit{ Q_NULLPTR };
    QMenu* m_pMainMenu{ Q_NULLPTR };
    QMenu* m_pUserMenu{ Q_NULLPTR };
};

#endif // TITLE_BAR_WIDGET_H
