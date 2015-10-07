#ifndef ZHUMA_H
#define ZHUMA_H

#include "luqucheck.h"
#include "chengjicheck.h"
#include "login.h"
#include "kechengbiaocheck.h"
#include "aboutwidget.h"
#include "feedback.h"
#include "cetcheck.h"

#include <QMainWindow>
#include <QResizeEvent>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>

namespace Ui {
class ZhuMa;
}

class ZhuMa : public QMainWindow
{
    Q_OBJECT

public:
    explicit ZhuMa(QWidget *parent = 0);
    ~ZhuMa();

protected:
    void resizeEvent(QResizeEvent *e);

public slots:
    void showChengjiCheck();
    void setSchoolLogo();
    void unOpenTips();
    void showLuQuCheck();
    void openSchoolWebSite();

private:
    Ui::ZhuMa *ui;

    QNetworkAccessManager m_manager;
    QNetworkCookieJar m_cookieJar;

    ChengJiCheck m_chengjiCheck;
    Login m_loginWindow;
    KeChengBiaoCheck m_kcbCheck;
    AboutWidget m_aboutWidget;
    FeedBack m_feedBack;
    CETCheck m_cetCheck;
};

#endif // ZHUMA_H
