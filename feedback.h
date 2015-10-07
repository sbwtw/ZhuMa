#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class FeedBack;
}

class FeedBack : public QWidget
{
    Q_OBJECT

public:
    explicit FeedBack(QWidget *parent = 0);
    ~FeedBack();

    void setNam(QNetworkAccessManager *manager);

public slots:
    void submitFeedBack();
    void submitFeedBack_finish();

    void show();

private:
    Ui::FeedBack *ui;

    QNetworkAccessManager *m_manager;
};

#endif // FEEDBACK_H
