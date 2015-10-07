
#include "displaykechengbiaomodel.h"
#include "helper.h"

#include <QRegExp>
#include <QString>

DisplayKeChengBiaoModel::DisplayKeChengBiaoModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    this->resetData();
}

void DisplayKeChengBiaoModel::resetData()
{
    m_kcb.clear();

    for (int i(0); i != 7; ++i)
    {
        QList<QString> row;
        for (int j(0); j != 5; ++j)
        {
            row.append(QString());
        }
        m_kcb.append(row);
    }
}

void DisplayKeChengBiaoModel::setData(int time, const QString &type)
{
    QString project = type;
//    project = project.replace("<br><br>", "\n");
    project = project.replace(QRegExp("<br>([-\\d]+)(?:<br>)+\\\\u5468<br>"), "\n\\1周 ");
    project = project.replace(QRegExp("<br>([^<]+)\\\\u5468(?:<br>)+"), "\n\\1周 ");
    project = project.replace("<br>\\u5468<br>", "周 ");
    project = project.replace("<br>", "-");

    m_kcb[time / 10 - 1][time % 10 - 1] = StringHelper::esacpe(project);
}

int DisplayKeChengBiaoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 7;
}

int DisplayKeChengBiaoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 5;
}

Qt::ItemFlags DisplayKeChengBiaoModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

QVariant DisplayKeChengBiaoModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return m_kcb[index.row()][index.column()];

    return QVariant();
}

QVariant DisplayKeChengBiaoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Vertical)
        {
            switch (section)
            {
            case 0:     return "周\n一";
            case 1:     return "周\n二";
            case 2:     return "周\n三";
            case 3:     return "周\n四";
            case 4:     return "周\n五";
            case 5:     return "周\n六";
            case 6:     return "周\n日";
            }
        }
        else if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:     return "上午1-2节";
            case 1:     return "上午3-4节";
            case 2:     return "下午5-6节";
            case 3:     return "下午7-8节";
            case 4:     return "晚上9-10节";
            }
        }
    }

    return QVariant();
}
