#ifndef RESETDATA_H
#define RESETDATA_H

#include <QString>
#include <QDateTime>
#include "resettype.h"

struct ResetData
{
    QDateTime timeTillReset;
    ResetType resetType;
};

#endif // RESETDATA_H
