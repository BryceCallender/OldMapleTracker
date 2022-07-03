#ifndef MAPLEACTION_H
#define MAPLEACTION_H

#include <QDateTime>
#include <QString>

struct MapleAction
{
    QString name;
    int order;
    bool done;

    bool isTemporary;
    QDateTime removalTime;
};

#endif // MAPLEACTION_H
