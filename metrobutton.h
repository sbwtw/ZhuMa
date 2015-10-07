#ifndef METROBUTTON_H
#define METROBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QResizeEvent>

class MetroButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit MetroButton(QWidget *parent = 0);

    void setIcon(const QIcon &icon);
    const QIcon icon();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *e);

public slots:
    void setToSquare();

private:
    QIcon m_icon;
};

#endif // METROBUTTON_H
