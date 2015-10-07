#ifndef DISPLAYKECHENGBIAOMODEL_H
#define DISPLAYKECHENGBIAOMODEL_H

#include <QAbstractTableModel>
#include <QList>

class DisplayKeChengBiaoModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DisplayKeChengBiaoModel(QObject *parent = 0);

    void resetData();
    void setData(int time, const QString &type);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:

private:
    QList<QList<QString>> m_kcb;
};

#endif // DISPLAYKECHENGBIAOMODEL_H
