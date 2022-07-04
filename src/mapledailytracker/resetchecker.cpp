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

bool ResetChecker::hasReset(const QDateTime& timeTillReset, const QDateTime& currentDateTime)
{
    int msecs = currentDateTime.time().msecsSinceStartOfDay();
    QDateTime resetTime = timeTillReset.addMSecs(msecs);
    // just force it to be 0 to make calculations correct
    resetTime.setTime(QTime(0,0,0));

    qint64 secs = currentDateTime.secsTo(resetTime);
    return secs <= 0 && secs >= -5;
}

int ResetChecker::daysTillWeekly(int resetDay, const QDateTime& currentDateTime)
{
    int dayOfWeek = currentDateTime.date().dayOfWeek();

    int distanceFromResetDay = qAbs(resetDay - dayOfWeek);

    if (dayOfWeek >= resetDay)
    {
        distanceFromResetDay = Qt::Sunday - distanceFromResetDay;
    }

    if (currentDateTime.time().msecsSinceStartOfDay() > 0)
    {
        --distanceFromResetDay;
    }

    return distanceFromResetDay;
}

ResetData ResetChecker::calcReset(int days, const QDateTime& currentDateTime)
{
    QDateTime tomorrow = currentDateTime.addDays(1);
    tomorrow.setTime(QTime(0,0,0)); //make it start of the next day

    qint64 secondsTillReset = currentDateTime.secsTo(tomorrow);
    QTime timeTillReset = QTime::fromMSecsSinceStartOfDay(secondsTillReset * 1000);

    QDate resetDate = tomorrow.date().addDays(days);

    ResetData resetData;
    resetData.timeTillReset = QDateTime(resetDate, timeTillReset, Qt::TimeSpec::UTC);
    return resetData;
}

QString ResetChecker::resetToLabel(const QDateTime &resetDateTime, const QDateTime& currentDateTime)
{
    QString label;

    QDateTime resetDate(resetDateTime);
    resetDate.setTime(QTime(0,0,0));
    QTime time = resetDateTime.time();

    qint64 secondsTill = currentDateTime.secsTo(resetDate);
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
