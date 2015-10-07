#include "login.h"
#include "helper.h"
#include "ui_login.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QRegExp>
#include <QPixmap>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QByteArray>
#include <QTextCodec>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login), m_logined(false)
{
    ui->setupUi(this);

    ui->pgs_watting->hide();

    ui->cmb_userType->addItem("学生", "student");
    ui->cmb_userType->addItem("家长", "Parents");
    ui->cmb_userType->setCurrentIndex(1);
    ui->edt_userId->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->edt_authMark->setVisible(false);

    connect(this, SIGNAL(loginSuccess()), this, SLOT(hide()));
    connect(this, SIGNAL(loginFail()), this, SLOT(getAuthMark()));
    connect(ui->btn_login, SIGNAL(clicked()), this, SLOT(login()));
//    connect(ui->btn_verifyCode, SIGNAL(clicked()), this, SLOT(getAuthMark()));
}

Login::~Login()
{
    delete ui;
}

const QString Login::getUserName() const
{
    return m_userName;
}

bool Login::isLogined() const
{
    return m_logined;
}

void Login::setNam(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

void Login::getAuthMark()
{
    const QUrl url("http://my.npumd.cn/Modu/userlogin.php");
    QNetworkReply *reply = m_manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), this, SLOT(getAuthMark_finish()));
}

void Login::getAuthMark_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());

    const QString response(reply->readAll());
    QRegExp regexp("AuthMark\" value=\"(\\w+)");

    if (regexp.indexIn(response) == -1)
    {
        QMessageBox::warning(this, "Error", "加载失败！");
        goto end;
    }

    ui->edt_authMark->setText(regexp.cap(1));

    this->getVerifyCode();
    end:
    reply->deleteLater();
}

void Login::getVerifyCode()
{
    const QUrl url("http://my.npumd.cn/Inc/ShowAuth.php");

    QNetworkReply *reply = m_manager->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()), this, SLOT(gteVeirfyCode_finish()));
}

void Login::gteVeirfyCode_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    QPixmap verifyCode;

    verifyCode.loadFromData(reply->readAll());
    verifyCode = verifyCode.scaledToHeight(24);

    ui->lab_verifyCode->setPixmap(verifyCode);
    reply->deleteLater();
}

void Login::login()
{
    ui->pgs_watting->show();
    const QUrl url = QString("http://my.npumd.cn/Inc/AjaxAct.php?Module=userlogin&Act=userlogin&Usr=%1&Pwd=%2&UserType=%3&div=%23ld")
                                .arg(ui->edt_userId->text())
                                .arg(StringHelper::md5(StringHelper::md5(ui->edt_userPwd->text()) + ui->edt_authMark->text()))
                                .arg(ui->cmb_userType->currentData().toString());

    QNetworkReply *reply = m_manager->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()), this, SLOT(login_finish()));
}

void Login::login_finish()
{
    ui->pgs_watting->hide();
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    const QString response(reply->readAll());
    QRegExp regexp("\\\\u767b\\\\u5f55\\\\u6210\\\\u529f\\(([^\\)]+)");

    if (regexp.indexIn(response) != -1)
    {
        m_userName = StringHelper::esacpe(regexp.cap(1));
        m_userId = ui->edt_userId->text();
        m_logined = true;

//        QMessageBox::information(this, "成功", "登陆成功！");

        emit loginSuccess();
    }
    else
    {
        QMessageBox::warning(this, "错误", "登陆失败！");

        emit loginFail();
    }

    reply->deleteLater();
}

void Login::logout()
{
    if (m_logined)
    {
        m_logined = false;
        QMessageBox::information(this, "退出登陆", "用户<" + m_userName + ">已退出登陆！");
    }
    else
    {
        QMessageBox::information(this, "退出登陆", "未登陆");
    }
}

void Login::show()
{
    QWidget::show();
    this->getAuthMark();
}
