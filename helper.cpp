#include "helper.h"

#include <QByteArray>
#include <QRegExp>
#include <QCryptographicHash>

const QString StringHelper::md5(const QString &str)
{
    QByteArray barray = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5);

    return barray.toHex();
}

const QString StringHelper::esacpe(QString str)
{
    QRegExp regexp("(\\\\u\\w{4})");
    int pos = 0;

    while ((pos = regexp.indexIn(str, pos)) != -1)
        str.replace(pos++, 6, QChar(regexp.cap(1).right(4).toUShort(0, 16)));

    return str;
}
