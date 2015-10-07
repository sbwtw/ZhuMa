
#include "zhuma.h"
#include "aboutwidget.h"
#include "ui_zhuma.h"

#include <QMessageBox>
#include <QPixmap>
#include <QIcon>
#include <QScroller>
#include <QMessageBox>
#include <QDesktopServices>

ZhuMa::ZhuMa(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ZhuMa)
{
    ui->setupUi(this);

    m_manager.setCookieJar(&m_cookieJar);

    m_chengjiCheck.setNam(&m_manager);
    m_loginWindow.setNam(&m_manager);
    m_kcbCheck.setNam(&m_manager);
    m_cetCheck.setNam(&m_manager);
    m_aboutWidget.setNam(&m_manager);
    m_feedBack.setNam(&m_manager);

//    ui->mbtn_feedBack->setBackgroundColor(QColor(220, 83, 83));
//    ui->mbtn_chengjiCheck->setBackgroundColor(QColor(83, 220, 196));
//    ui->mbtn_cetCheck->setBackgroundColor(QColor(131, 220, 83));
//    ui->mbtn_luquCheck->setBackgroundColor(QColor(220, 147, 83));
//    ui->mbtn_library->setBackgroundColor(QColor(227, 225, 57));
//    ui->mbtn_keChengBiao->setBackgroundColor(QColor(103, 147, 206));
//    ui->mbtn_schoolWebSite->setBackgroundColor(QColor(237, 67, 188));
//    ui->mbtn_boYinCheck->setBackgroundColor(QColor(167, 84, 204));

    ui->mbtn_feedBack->setIcon(QIcon(":/ZhuMa/resources/icons/feedReport.png"));
    ui->mbtn_chengjiCheck->setIcon(QIcon(":/ZhuMa/resources/icons/cjCheck.png"));
    ui->mbtn_about->setIcon(QIcon(":/ZhuMa/resources/icons/about.png"));
    ui->mbtn_luquCheck->setIcon(QIcon(":/ZhuMa/resources/icons/gkCheck.png"));
    ui->mbtn_library->setIcon(QIcon(":/ZhuMa/resources/icons/library.png"));
    ui->mbtn_keChengBiao->setIcon(QIcon(":/ZhuMa/resources/icons/kcb.png"));
    ui->mbtn_schoolWebSite->setIcon(QIcon(":/ZhuMa/resources/icons/schoolWeb.png"));
    ui->mbtn_boYinCheck->setIcon(QIcon(":/ZhuMa/resources/icons/byzcCheck.png"));
    ui->mbtn_discover->setIcon(QIcon(":/ZhuMa/resources/icons/discover.png"));
    ui->mbtn_shop->setIcon(QIcon(":/ZhuMa/resources/icons/shop.png"));

    connect(ui->mbtn_discover, SIGNAL(clicked()), this, SLOT(unOpenTips()));
    connect(ui->mbtn_shop, SIGNAL(clicked()), this, SLOT(unOpenTips()));
    connect(ui->mbtn_boYinCheck, SIGNAL(clicked()), this, SLOT(unOpenTips()));
    connect(ui->mbtn_library, SIGNAL(clicked()), this, SLOT(unOpenTips()));
    connect(ui->mbtn_schoolWebSite, SIGNAL(clicked()), this, SLOT(openSchoolWebSite()));
    connect(ui->mbtn_chengjiCheck, SIGNAL(clicked()), this, SLOT(showChengjiCheck()));
    connect(ui->mbtn_luquCheck, SIGNAL(clicked()), this, SLOT(showLuQuCheck()));
    connect(ui->mbtn_feedBack, SIGNAL(clicked()), &m_feedBack, SLOT(show()));
    connect(ui->mbtn_about, SIGNAL(clicked()), &m_aboutWidget, SLOT(show()));
    connect(ui->mbtn_keChengBiao, SIGNAL(clicked()), &m_kcbCheck, SLOT(show()));
    connect(ui->act_aboutZhuMa, SIGNAL(triggered()), &m_aboutWidget, SLOT(show()));
    connect(ui->act_exitZhuMa, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->act_exitLogin, SIGNAL(triggered()), &m_loginWindow, SLOT(logout()));

    // 先進行一次http操作可以申請一部分內存，減小之後操作的卡頓
    m_aboutWidget.checkUpdate();

    QScroller::grabGesture(ui->sca_buttonList, QScroller::LeftMouseButtonGesture);
}

ZhuMa::~ZhuMa()
{
    delete ui;
}

void ZhuMa::resizeEvent(QResizeEvent *e)
{
    this->setSchoolLogo();
    QMainWindow::resizeEvent(e);
}

void ZhuMa::showChengjiCheck()
{
    if (!m_loginWindow.isLogined())
    {
        m_loginWindow.show();
        connect(&m_loginWindow, SIGNAL(loginSuccess()), &m_chengjiCheck, SLOT(show()));
    }
    else
    {
        m_chengjiCheck.show();
    }
}

void ZhuMa::setSchoolLogo()
{
    QPixmap schoolIcon(":/ZhuMa/resources/Npumd.png");
    schoolIcon = schoolIcon.scaledToWidth(ui->lab_schoolIcon->width());
    ui->lab_schoolIcon->setPixmap(schoolIcon);
}

void ZhuMa::unOpenTips()
{
    QMessageBox::information(this, "( >﹏<。)", "此功能暂未开放");
}

void ZhuMa::showLuQuCheck()
{
    LuQuCheck luqu(this);
    luqu.setNam(&m_manager);
    luqu.exec();
}

void ZhuMa::openSchoolWebSite()
{
    QDesktopServices::openUrl(QUrl("http://www.npumd.edu.cn/"));
}
