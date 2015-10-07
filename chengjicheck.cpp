#include "chengjicheck.h"
#include "ui_chengjicheck.h"

#include <QScroller>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

ChengJiCheck::ChengJiCheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChengJiCheck)
{
    ui->setupUi(this);

    QScroller::grabGesture(ui->txtb_response, QScroller::LeftMouseButtonGesture);
}

ChengJiCheck::~ChengJiCheck()
{
    delete ui;
}

void ChengJiCheck::setNam(QNetworkAccessManager *manager)
{
    this->m_manager = manager;
}

void ChengJiCheck::show()
{
    ui->txtb_response->setText("正在查询...");
    this->getChengJiResponse();

    QWidget::show();
}

void ChengJiCheck::getChengJiResponse()
{
    const QUrl url("http://my.npumd.cn/Modu/ScoreTerm.php");
    QNetworkReply *reply = m_manager->get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()), this, SLOT(getChengJiResponse_finish()));
}

void ChengJiCheck::getChengJiResponse_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    const QString response(reply->readAll());

    ui->txtb_response->setHtml(response);

    reply->deleteLater();
}
