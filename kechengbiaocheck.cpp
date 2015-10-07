#include "kechengbiaocheck.h"
#include "ui_kechengbiaocheck.h"

#include <QUrl>
#include <QRegExp>
#include <QString>
#include <QMessageBox>

KeChengBiaoCheck::KeChengBiaoCheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeChengBiaoCheck)
{
    ui->setupUi(this);

    ui->cmb_type->addItem("班级课表", "Class");
    ui->cmb_type->addItem("教室课表", "ClassRoom");
    ui->cmb_type->addItem("课程课表", "Lession");

    ui->cmb_queryXueQi->addItem("第一学期", "1");
    ui->cmb_queryXueQi->addItem("第二学期", "2");
    ui->cmb_queryXueQi->addItem("第三学期", "3");

    ui->text_infoNumber->setInputMethodHints(Qt::ImhDigitsOnly);
    ui->spb_queryYear->setInputMethodHints(Qt::ImhDigitsOnly);

    ui->pgb_query->hide();

    connect(ui->cmb_type, SIGNAL(currentIndexChanged(int)), this, SLOT(queryTypeChange()));
    connect(ui->btn_query, SIGNAL(clicked()), this, SLOT(queryKCB()));

//    this->setWindowFlags(Qt::Window);
//    this->setAttribute(Qt::WA_AcceptTouchEvents);
}

KeChengBiaoCheck::~KeChengBiaoCheck()
{
    delete ui;
}

void KeChengBiaoCheck::setNam(QNetworkAccessManager *manager)
{
    m_manager = manager;
}

void KeChengBiaoCheck::queryTypeChange()
{
    switch (ui->cmb_type->currentIndex())
    {
    case 0:     ui->lab_infoNumber->setText("班级号码: ");        break;
    case 1:     ui->lab_infoNumber->setText("教室编号: ");        break;
    case 2:     ui->lab_infoNumber->setText("课程名称: ");        break;
    }
}

void KeChengBiaoCheck::queryKCB()
{
    ui->pgb_query->show();
    this->update();

    QString url;
    url += "http://my.npumd.cn/Inc/AjaxAct.php?Module=Curriculum&Act=Curriculum&Data4Url=InYear%3D";
    url += QString::number(ui->spb_queryYear->value());
    url += "%26InTermNum%3D";
    url += ui->cmb_queryXueQi->currentData().toString();
    url += "%26InType%3D";
    url += ui->cmb_type->currentData().toString();
    url += "%26InValue%3D";
    url += ui->text_infoNumber->text().replace("#", "%23");
//    if (ui->text_queryWeek->text().toInt() >= 0)
//    {
//        url += "%26InWeek%3D";
//        url += ui->text_queryWeek->text();
//    }
    url += "%26CurYear%3D2014%26CurTermNum%3D1";

    QNetworkReply *reply = m_manager->get(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(finished()), this, SLOT(queryKCB_finish()));
}

void KeChengBiaoCheck::queryKCB_finish()
{
    QNetworkReply *reply = static_cast<QNetworkReply *>(sender());
    QString response = reply->readAll();
    reply->deleteLater();

    ui->pgb_query->hide();

    QRegExp regexp("#L(\\d+)'\\)\\.html\\(\\)\\+\\\\\"([^\\$]+)<br><br>\\\\\"\\);");
    int index = 0;

    m_kcbWidget.resetData();
    while ((index = regexp.indexIn(response, index)) != -1)
    {
        m_kcbWidget.setData(regexp.cap(1).toInt(), regexp.cap(2));

        index += regexp.matchedLength();
    }

    m_kcbWidget.show();
}
