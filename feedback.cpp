#include "feedback.h"
#include "ui_feedback.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <QRegExp>
#include <QUrlQuery>

FeedBack::FeedBack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeedBack)
{
    ui->setupUi(this);

    ui->pgs_submitting->hide();

    connect(ui->btn_submit, SIGNAL(clicked()), this ,SLOT(submitFeedBack()));
}

FeedBack::~FeedBack()
{
    delete ui;
}

void FeedBack::setNam(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

void FeedBack::submitFeedBack()
{
    QString content(ui->text_content->toPlainText());
    QString email(ui->text_email->text());
    QRegExp regexp("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");

    if (content.isEmpty())
    {
        QMessageBox::critical(this, "坑爹呢這是!", "至少说句话呀(°Д°)!");
        return ;
    }
    if (email.isEmpty() || !regexp.exactMatch(email))
    {
        QMessageBox::critical(this, "不乖哦~", "为什么不交出水表呢 (ง •̀_•́)ง");
        return ;
    }

    QUrl url("http://zhuma.sbw.so/feedBack.php");
    QUrlQuery query;
    query.addQueryItem("content", content);
    query.addQueryItem("email", email);
    url.setQuery(query);

    QNetworkReply *reply = m_manager->post(QNetworkRequest(url), url.query().toStdString().c_str());
    connect(reply, SIGNAL(finished()), this, SLOT(submitFeedBack_finish()));

    ui->pgs_submitting->show();
}

void FeedBack::submitFeedBack_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());

    QMessageBox::information(this, "提示", reply->readAll());
    reply->deleteLater();

    ui->pgs_submitting->hide();
    ui->text_content->clear();
    ui->text_email->clear();
}

void FeedBack::show()
{
    ui->text_content->clear();
    ui->text_email->clear();
    QWidget::show();
}
