#include "cetcheck.h"
#include "ui_cetcheck.h"

#include <QPixmap>
#include <QMessageBox>
#include <QNetworkRequest>

CETCheck::CETCheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CETCheck)
{
    ui->setupUi(this);

//    ui->text_yzmAddress->hide();
    ui->pgs_waitting->hide();

//    ui->cmb_quertType->addItem("英語四級", "CET-4");
//    ui->cmb_quertType->addItem("英語六級", "CET-6");
////    ui->cmb_quertType->addItem("日語四級", "JET-4");
////    ui->cmb_quertType->addItem("日語六級", "JET-6");
////    ui->cmb_quertType->addItem("德語四級", "GET-4");
////    ui->cmb_quertType->addItem("德語六級", "GET-6");
////    ui->cmb_quertType->addItem("俄語四級", "RET-4");
////    ui->cmb_quertType->addItem("俄語六級", "RET-6");
////    ui->cmb_quertType->addItem("法語四級", "FET-4");

//    ui->cmb_numberType->addItem("身份證號", "sfzh");
//    ui->cmb_numberType->addItem("準考證號", "zkzh");

    connect(ui->btn_query, SIGNAL(clicked()), this, SLOT(queryCET()));
}

CETCheck::~CETCheck()
{
    delete ui;
}

void CETCheck::setNam(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

void CETCheck::show()
{
//    this->fetchIndex();
    QWidget::show();
}

//void CETCheck::fetchIndex()
//{
//    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl("http://my.npumd.cn/Modu/userlogin.php")));
//    connect(reply, SIGNAL(finished()), this, SLOT(fetchIndex_finish()));
//}

//void CETCheck::fetchIndex_finish()
//{
//    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());

//    const QString response(reply->readAll());
//    QRegExp regexp("AuthMark\" value=\"(\\w+)");

//    if (regexp.indexIn(response) == -1)
//    {
//        QMessageBox::warning(this, "Error", "加载失败！");
//        goto end;
//    }

//    ui->text_yzmAddress->setText(regexp.cap(1));

//    this->getYzmPic();
//    end:
//    reply->deleteLater();
//}

//void CETCheck::getYzmPic()
//{
//    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl("http://my.npumd.cn/Inc/ShowAuth.php")));
//    connect(reply, SIGNAL(finished()), this, SLOT(getYzmPic_finish()));
//}

//void CETCheck::getYzmPic_finish()
//{
//    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
//    QPixmap verifyCode;

//    verifyCode.loadFromData(reply->readAll());
//    verifyCode = verifyCode.scaledToHeight(ui->lab_yzm->height());

//    ui->lab_yzm->setPixmap(verifyCode);
//    reply->deleteLater();
//}

void CETCheck::queryCET()
{
    ui->pgs_waitting->show();

    QString url("http://www.chsi.com.cn/cet/query?zkzh=");
    url += ui->text_number->text();
    url += "&xm=";
    url += ui->text_name->text();

    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader("Hots", "www.chsi.com.cn");
    req.setRawHeader("Referer", "http://www.chsi.com.cn/cet/");
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(finished()), this, SLOT(queryCET_finish()));
}

void CETCheck::queryCET_finish()
{
    ui->pgs_waitting->hide();
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    QString response = reply->readAll();
    reply->deleteLater();

    QMessageBox::information(this, "a", response);
}
