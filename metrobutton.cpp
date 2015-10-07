#include "metrobutton.h"

#include <QPushButton>
#include <QPainter>
#include <QStyleOptionButton>

MetroButton::MetroButton(QWidget *parent) :
    QAbstractButton(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void MetroButton::setIcon(const QIcon &icon)
{
    m_icon = icon;
}

const QIcon MetroButton::icon()
{
    return m_icon;
}

void MetroButton::resizeEvent(QResizeEvent *e)
{
    this->setToSquare();

    QAbstractButton::resizeEvent(e);
}

// 最好應該自己重畫，先這樣用着
void MetroButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter p(this);

    p.drawPixmap(0, 0, this->width(), this->height(), m_icon.pixmap(this->width(), this->height()));

//    p.fillRect(0, 0, this->width(), this->height(), m_backgroundColor);

//    QStyleOptionButton option;
//    option.initFrom(this);
//    option.icon = m_icon;

//    p.drawControl(QStyle::CE_PushButton, option);
}

void MetroButton::setToSquare()
{
//    if (this->width() > this->height())
        this->setMinimumHeight(this->width());
//    else
//        this->setMinimumWidth(this->height());
}
