#ifndef KECHENGBIAOCHECK_H
#define KECHENGBIAOCHECK_H

#include "displaykechengbiao.h"

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class KeChengBiaoCheck;
}

class KeChengBiaoCheck : public QWidget
{
    Q_OBJECT

public:
    explicit KeChengBiaoCheck(QWidget *parent = 0);
    ~KeChengBiaoCheck();

    void setNam(QNetworkAccessManager *manager);

public slots:
    void queryTypeChange();
    void queryKCB();
    void queryKCB_finish();

private:
    Ui::KeChengBiaoCheck *ui;

    QNetworkAccessManager *m_manager;
    DisplayKeChengBiao m_kcbWidget;
};

#endif // KECHENGBIAOCHECK_H
