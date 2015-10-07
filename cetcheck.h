#ifndef CETCHECK_H
#define CETCHECK_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class CETCheck;
}

class CETCheck : public QWidget
{
    Q_OBJECT

public:
    explicit CETCheck(QWidget *parent = 0);
    ~CETCheck();

    void setNam(QNetworkAccessManager *manager);

public slots:
    void show();

//    void fetchIndex();
//    void fetchIndex_finish();
//    void getYzmPic();
//    void getYzmPic_finish();
    void queryCET();
    void queryCET_finish();

private:
    Ui::CETCheck *ui;

    QNetworkAccessManager *m_manager;
};

#endif // CETCHECK_H
