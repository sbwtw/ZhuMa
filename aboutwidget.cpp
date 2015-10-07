#include "aboutwidget.h"
#include "ui_aboutwidget.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QDesktopServices>

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);

    ui->lab_version->setText(QString("v ") + QString(VERSION));

    connect(ui->btn_checkUpdate, SIGNAL(clicked()), this, SLOT(checkUpdate()));
    connect(ui->btn_authorBlog, SIGNAL(clicked()), this, SLOT(openAuthorBlog()));
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::setNam(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

void AboutWidget::checkUpdate()
{
    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl("http://zhuma.sbw.so/version")));
    connect(reply, SIGNAL(finished()), this, SLOT(checkUpdate_finish()));

    ui->lab_versionTips->setText("正在检查更新...");
}

void AboutWidget::checkUpdate_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    QString version(reply->readAll());
    reply->deleteLater();

    if (version == VERSION)
    {
        ui->lab_versionTips->setText("您当前使用的为最新版竹马！");
//        QMessageBox::information(this, "版本信息", "您当前使用的为最新版竹马！");
    }
    else if (!version.isEmpty())
    {
        ui->lab_versionTips->setText("发现新版本！");
        QMessageBox::StandardButton button = QMessageBox::information(this, "发现新版本", "最新版本为" + version + ", 是否立即下载？", QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes);
        if (button == QMessageBox::Yes)
            QDesktopServices::openUrl(QUrl("http://download.sbw.so/ZhuMa-latest.apk"));
    }
    else
    {
        ui->lab_versionTips->setText("网络连接出错！");
    }
}

void AboutWidget::openAuthorBlog()
{
    QDesktopServices::openUrl(QUrl("http://blog.sbw.so/"));
}

void AboutWidget::show()
{
    ui->lab_versionTips->clear();

    QWidget::show();
}
