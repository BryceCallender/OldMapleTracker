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

    bool hasReset(const QDateTime& resetTime, const QDateTime& currentDateTime = QDateTime::currentDateTimeUtc());

    static QString resetToLabel(const QDateTime& resetDateTime, const QDateTime& currentDateTime = QDateTime::currentDateTimeUtc());
private:
    int daysTillWeekly(int resetDay = Qt::Thursday, const QDateTime& currentDateTime = QDateTime::currentDateTimeUtc());
    ResetData calcReset(int days = 0, const QDateTime& currentDateTime = QDateTime::currentDateTimeUtc());
    QDateTime lastOpened;
};

#endif // RESETCHECKER_H
