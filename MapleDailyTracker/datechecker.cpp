#include "datechecker.h"

DateChecker::DateChecker()
{
    lastOpened = QDateTime::currentDateTimeUtc();
    midnight.setHMS(23,59,59);
    resetTime = midnight;
}

QTime DateChecker::timeTillDailyReset()
{
    ResetData resetData = calcReset(ResetType::Daily);
    return resetData.timeTillReset;
}

QTime DateChecker::timeTillWeeklyReset()
{
    int days = daysTillWeekly();
    ResetData resetData = calcReset(ResetType::Weekly, days);
    return resetData.timeTillReset;
}

int DateChecker::daysTillWeekly()
{
    QDateTime currentDateTimeUTC = QDateTime::currentDateTimeUtc();

    int resetDayOfWeek = Qt::Thursday;
    int dayOfWeek = currentDateTimeUTC.date().dayOfWeek();

    return dayOfWeek % resetDayOfWeek;
}

ResetData DateChecker::calcReset(ResetType resetType, int days)
{
    QDateTime currentDateTimeUTC = QDateTime::currentDateTimeUtc();

    QDateTime tomorrow = currentDateTimeUTC.addDays(1);
    tomorrow.setTime(QTime(0,0,0)); //make it start of the next day

    qint64 secondsTillReset = currentDateTimeUTC.secsTo(tomorrow);
    QTime timeTillReset = QTime::fromMSecsSinceStartOfDay(secondsTillReset * 1000);

    if (days > 0)
    {
        int secondsToNextDate = timeTillReset.secsTo(tomorrow.addDays(days).time());
        timeTillReset = timeTillReset.addSecs(secondsToNextDate);
    }

    ResetData resetData;
    resetData.timeTillReset = timeTillReset;
    resetData.resetType = resetType;
    return resetData;
}
