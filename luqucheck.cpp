#include "luqucheck.h"
#include "helper.h"
#include "ui_luqucheck.h"

#include <QList>
#include <QString>
#include <QScroller>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QString>
#include <QDebug>

LuQuCheck::LuQuCheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LuQuCheck)
{
    ui->setupUi(this);

    ui->cmb_ids->addItem("身份证号", QVariant("sfzh"));
    ui->cmb_ids->addItem("准考证号", QVariant("zkzh"));
    ui->cmb_ids->setCurrentIndex(0);
    ui->edt_id->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->pgs_querying->setVisible(false);

    //connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(netWorkAccess_finish(QNetworkReply*)));
    connect(ui->btn_query, SIGNAL(clicked()), this, SLOT(luquCheck()));

    this->setWindowFlags(Qt::Window);

    QScroller::grabGesture(ui->txtb_tips, QScroller::LeftMouseButtonGesture);
}

LuQuCheck::~LuQuCheck()
{
    delete ui;
}

void LuQuCheck::setNam(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

void LuQuCheck::luquCheck()
{
    QString url;
    url += "http://my.npumd.cn/Inc/AjaxAct.php?Module=SearchGklq&Act=&Data4Url=SearchField%3D";
    url += ui->cmb_ids->currentData().toString();
    url += "%26SearchValue%3D";
    url += ui->edt_id->text();

    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl(url)));

    connect(reply, SIGNAL(finished()), this, SLOT(luquCheck_finish()));

    ui->pgs_querying->setVisible(true);
}

void LuQuCheck::luquCheck_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    ui->pgs_querying->setVisible(false);

    const QString response(reply->readAll());
    QJsonDocument document = QJsonDocument::fromJson(response.toStdString().c_str());

    if (!document.isObject() || !document.object().contains("Rst") || !document.object()["Rst"].toBool())
    {
        QMessageBox::warning(this, "查询失败", "无录取信息！");
        return ;
    }

    QRegExp regexp(">([\\\\\\w]+)<\\\\\\/td><\\\\\\/tr><\\\\\\/table>\\\"");

    if (regexp.indexIn(response) != -1)
        QMessageBox::information(this, "Congratulations!", "您已被我校 <" + StringHelper::esacpe(regexp.cap(1)) + "> 专业录取！");
    else
        QMessageBox::information(this, "Congratulations!", "您已被我校录取！");
}
