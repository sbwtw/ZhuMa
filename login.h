#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

public:
    const QString getUserName() const;
    bool isLogined() const;

    void setNam(QNetworkAccessManager *manager);

signals:
    void loginSuccess();
    void loginFail();

public slots:
    void getAuthMark();
    void getAuthMark_finish();
    void getVerifyCode();
    void gteVeirfyCode_finish();
    void login();
    void login_finish();
    void logout();

    void show();

private:
    Ui::Login *ui;

    QString m_userName;
    QString m_userId;
    QNetworkAccessManager *m_manager;

    bool m_logined;
};

#endif // LOGIN_H
