#include "resetchecker.h"

ResetChecker::ResetChecker()
{
    lastOpened = QDateTime::currentDateTimeUtc();
}

QDateTime ResetChecker::timeTillDailyReset()
{
    ResetData resetData = calcReset(ResetType::Daily);
    return resetData.timeTillReset;
}

QDateTime ResetChecker::timeTillWeeklyReset(int resetDay)
{
    int days = daysTillWeekly(resetDay);
    ResetData resetData = calcReset(ResetType::Weekly, days);
    return resetData.timeTillReset;
}

bool ResetChecker::isDailyReset()
{

}

bool ResetChecker::isWedWeeklyReset()
{

}

bool ResetChecker::isMonWeeklyReset()
{

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

ResetData ResetChecker::calcReset(ResetType resetType, int days)
{
    QDateTime currentDateTimeUTC = QDateTime::currentDateTimeUtc();

    QDateTime tomorrow = currentDateTimeUTC.addDays(1);
    tomorrow.setTime(QTime(0,0,0)); //make it start of the next day

    qint64 secondsTillReset = currentDateTimeUTC.secsTo(tomorrow);
    QTime timeTillReset = QTime::fromMSecsSinceStartOfDay(secondsTillReset * 1000);

    QDate resetDate = currentDateTimeUTC.date().addDays(days);

    ResetData resetData;
    resetData.timeTillReset = QDateTime(resetDate, timeTillReset);
    resetData.resetType = resetType;
    return resetData;
}

QString ResetChecker::resetToLabel(QDateTime resetDateTime)
{
    QString label;

    QDate currentUTCDate = QDateTime::currentDateTimeUtc().date();

    QDate date = resetDateTime.date();
    QTime time = resetDateTime.time();

    if (date.day() != currentUTCDate.day())
    {
        int days = currentUTCDate.daysTo(date);
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

    return label;
}
