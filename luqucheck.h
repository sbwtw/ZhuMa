#ifndef LUQUCHECK_H
#define LUQUCHECK_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class LuQuCheck;
}

class LuQuCheck : public QDialog
{
    Q_OBJECT

public:
    explicit LuQuCheck(QWidget *parent = 0);
    ~LuQuCheck();

    void setNam(QNetworkAccessManager *manager);

public slots:
    void luquCheck();
    void luquCheck_finish();

private:
    Ui::LuQuCheck *ui;

    QNetworkAccessManager *m_manager;
};

#endif // LUQUCHECK_H
