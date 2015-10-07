#ifndef DISPLAYKECHENGBIAO_H
#define DISPLAYKECHENGBIAO_H

#include "displaykechengbiaomodel.h"

#include <QDialog>

namespace Ui {
class DisplayKeChengBiao;
}

class DisplayKeChengBiao : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayKeChengBiao(QWidget *parent = 0);
    ~DisplayKeChengBiao();

    void show();

    void resetData();
    void setData(const int &time, const QString &type);

public slots:
    void saveAsPicture();

private:
    Ui::DisplayKeChengBiao *ui;

    DisplayKeChengBiaoModel *m_model;
};

#endif // DISPLAYKECHENGBIAO_H
