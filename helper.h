#ifndef HELPER_H
#define HELPER_H

#include<QString>

class StringHelper
{
public:
    static const QString md5(const QString &str);
    static const QString esacpe(QString str);
};

#endif // HELPER_H
