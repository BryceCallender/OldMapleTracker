#ifndef RESETCHECKER_H
#define RESETCHECKER_H

#include <QTime>
#include <QDebug>
#include "resetdata.h"

class ResetChecker
{
public:
    ResetChecker();
    QDateTime timeTillDailyReset();
    QDateTime timeTillWeeklyReset(int resetDay = Qt::Thursday);

    bool isDailyReset();
    bool isWedWeeklyReset();
    bool isMonWeeklyReset();

    static QString resetToLabel(QDateTime resetDateTime);
private:
    int daysTillWeekly(int resetDay = Qt::Thursday);
    ResetData calcReset(int days = 0);
    QDateTime lastOpened;
};

#endif // RESETCHECKER_H
