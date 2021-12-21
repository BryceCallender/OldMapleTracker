#ifndef DATECHECKER_H
#define DATECHECKER_H

#include <QTime>
#include <QDebug>
#include "ResetData.h"
#include "ResetType.h"

class DateChecker
{
public:
    DateChecker();
    QTime timeTillDailyReset();
    QTime timeTillWeeklyReset();
private:
    int daysTillWeekly();
    ResetData calcReset(ResetType resetType, int days = 0);
    QDateTime lastOpened;
    QTime resetTime;
    QTime midnight;
};

#endif // DATECHECKER_H
