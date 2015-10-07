#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class AboutWidget;
}

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = 0);
    ~AboutWidget();

    void setNam(QNetworkAccessManager *manager);

public slots:
    void checkUpdate();
    void checkUpdate_finish();
    void openAuthorBlog();

    void show();

private:
    Ui::AboutWidget *ui;

    QNetworkAccessManager *m_manager;
};

#endif // ABOUTDIALOG_H
