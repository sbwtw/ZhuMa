#ifndef CHENGJICHECK_H
#define CHENGJICHECK_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class ChengJiCheck;
}

class ChengJiCheck : public QWidget
{
    Q_OBJECT

public:
    explicit ChengJiCheck(QWidget *parent = 0);
    ~ChengJiCheck();

    void setNam(QNetworkAccessManager *manager);

public slots:
    void show();
    void getChengJiResponse();
    void getChengJiResponse_finish();

private:
    Ui::ChengJiCheck *ui;

    QNetworkAccessManager *m_manager;
};

#endif // CHENGJICHECK_H
