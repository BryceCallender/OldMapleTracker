#ifndef RESETCHECKER_H
#define RESETCHECKER_H

#include <QTime>
#include <QDebug>
#include "resetdata.h"
#include "resettype.h"

class ResetChecker
{
public:
    ResetChecker();
    QDateTime timeTillDailyReset();
    QDateTime timeTillWeeklyReset(int resetDay = Qt::Thursday);

    static QString resetToLabel(QDateTime resetDateTime);
private:
    int daysTillWeekly(int resetDay = Qt::Thursday);
    ResetData calcReset(ResetType resetType, int days = 0);
    QDateTime lastOpened;
};

#endif // RESETCHECKER_H
