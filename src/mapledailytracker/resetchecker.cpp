#include "resetchecker.h"

ResetChecker::ResetChecker()
{
    lastOpened = QDateTime::currentDateTimeUtc();
}

QDateTime ResetChecker::timeTillDailyReset()
{
    ResetData resetData = calcReset();
    return resetData.timeTillReset;
}

QDateTime ResetChecker::timeTillWeeklyReset(int resetDay)
{
    int days = daysTillWeekly(resetDay);
    ResetData resetData = calcReset(days);
    return resetData.timeTillReset;
}

bool ResetChecker::hasReset(const QDateTime& timeTillReset)
{
    QDateTime currentTimeUtc = QDateTime::currentDateTimeUtc();

    int msecs = currentTimeUtc.time().msecsSinceStartOfDay();
    QDateTime resetTime = timeTillReset.addMSecs(msecs);
    // just force it to be 0 to make calculations correct
    resetTime.setTime(QTime(0,0,0));

    return currentTimeUtc.secsTo(resetTime) <= 0;
}

int ResetChecker::daysTillWeekly(int resetDay)
{
    QDateTime currentDateTimeUTC = QDateTime::currentDateTimeUtc();

    int dayOfWeek = currentDateTimeUTC.date().dayOfWeek();

    int distanceFromResetDay = qAbs(resetDay - dayOfWeek);

    if (dayOfWeek >= resetDay)
    {
        distanceFromResetDay = Qt::Sunday - distanceFromResetDay;
    }

    if (currentDateTimeUTC.time().msecsSinceStartOfDay() > 0)
    {
        --distanceFromResetDay;
    }

    return distanceFromResetDay;
}

ResetData ResetChecker::calcReset(int days)
{
    QDateTime currentDateTimeUTC = QDateTime::currentDateTimeUtc();

    QDateTime tomorrow = currentDateTimeUTC.addDays(1);
    tomorrow.setTime(QTime(0,0,0)); //make it start of the next day

    qint64 secondsTillReset = currentDateTimeUTC.secsTo(tomorrow);
    QTime timeTillReset = QTime::fromMSecsSinceStartOfDay(secondsTillReset * 1000);

    QDate resetDate = tomorrow.date().addDays(days);

    ResetData resetData;
    resetData.timeTillReset = QDateTime(resetDate, timeTillReset, Qt::TimeSpec::UTC);
    return resetData;
}

QString ResetChecker::resetToLabel(const QDateTime &resetDateTime)
{
    QString label;

    QDateTime currentUTCDateTime = QDateTime::currentDateTimeUtc();

    QDateTime resetDate(resetDateTime);
    resetDate.setTime(QTime(0,0,0));
    QTime time = resetDateTime.time();

    qint64 secondsTill = currentUTCDateTime.secsTo(resetDate);
    int days = secondsTill / 86400.0;

    if (days > 0)
    {        
        label.append(QString::number(days) + "d ");
    }

    if (time.hour() > 0)
    {
        label.append(QString::number(time.hour()) + "h ");
    }

    if (time.minute() > 0)
    {
        label.append(QString::number(time.minute()) + "m ");
    }

    if (time.second() > 0)
    {
        label.append(QString::number(time.second()) + "s ");
    }

    return label;
}
