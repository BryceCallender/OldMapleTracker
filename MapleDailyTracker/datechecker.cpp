#include "datechecker.h"

DateChecker::DateChecker()
{
    QTime resetTime(0,0);

    midnight.setHMS(23,59,59);

    readFromFile();
}

bool DateChecker::isDailyReset()
{
    QDateTime currentTime = QDateTime::currentDateTimeUtc();
    QDateTime resetTime = lastTimeOpened.toUTC();

    //If we went pass the daily reset time and have not reset yet then
    //lets reset
    if(currentTime.date().day() > resetTime.date().day() && !hasResetDaily)
    {
        hasResetDaily = true;
    }
    else
    {
        hasResetDaily = false;
    }
    return hasResetDaily;
}

bool DateChecker::isWeeklyReset()
{
    QDateTime currentTime = QDateTime::currentDateTimeUtc();
    QDateTime resetTime = lastWeeklyResetTime.toUTC();

    if(currentTime.date().day() > resetTime.date().day() && !hasResetWeekly)
    {
        hasResetWeekly = true;
    }
    else
    {
        hasResetWeekly = false;
    }
    return hasResetWeekly;
}

QString DateChecker::timeTillDailyReset()
{
    return nextDailyReset().timeMessage;
}

QString DateChecker::timeTillWeeklyReset()
{
    return nextWeeklyReset().timeMessage;
}

ResetDate DateChecker::nextDailyReset()
{
    return calcTimeTillReset();
}

ResetDate DateChecker::nextWeeklyReset()
{
    QDateTime currentTime = QDateTime::currentDateTimeUtc();

    //Set time to UTC so i can be relating this for everytime
    //zone without having to worry about DST
    currentTime.setTimeSpec(Qt::UTC);

    int newDate = daysTillWeeklyReset(currentTime);

    return calcTimeTillReset(newDate, "Weekly");
}

ResetDate DateChecker::calcTimeTillReset(int days, QString type)
{
    QDateTime currentTime = QDateTime::currentDateTimeUtc();

    //Set time to UTC so i can be relating this for everytime
    //zone without having to worry about DST
    currentTime.setTimeSpec(Qt::UTC);

    int milliseconds = currentTime.time().msecsSinceStartOfDay();
    //Take what time we have since the beginning of the day and subtract it
    //since itll make us go past reset if we do not handle it
    QTime timeTillReset = midnight.addMSecs(-milliseconds);
    //since i cant do 24 hrs from now OMEGALUL
    timeTillReset = timeTillReset.addSecs(1);

    QString message;
    //Output statement showing how long till reset
    //message = "Next reset is in ";
    //If we have some days till reset lets show them if not dont
    if(days != 0)
    {
        message += QString::number(days) + " day(s) ";
    }
    message += QString::number(timeTillReset.hour()) + " hour(s), "
            + QString::number(timeTillReset.minute()) + " minute(s), "
            + QString::number(timeTillReset.second()) + " second(s)";

    //find how many seconds have elapsed since beginning of day for math reason
    int seconds = QTime(0,0,0).secsTo(timeTillReset);

    //update the time and date accordingly
    QTime updatedTime = currentTime.time().addSecs(seconds);
    // was 1 for some reason but want to add the days that we pass in
    QDate updatedDate = currentTime.date().addDays(days);

    QDateTime nextReset(updatedDate,updatedTime);
    nextReset.setTimeSpec(Qt::UTC);

    ResetDate reset;
    reset.timeMessage = message;
    reset.resetType = type;
    reset.resetTime = nextReset;

    return reset;
}

void DateChecker::writeToFile()
{
    QFile file("ResetsAndTime.txt");

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream fileStream(&file);
        fileStream << QDateTime::currentDateTime().toString() << "\n";
        fileStream << nextDailyReset().resetTime.toLocalTime().toString() << "\n";
        fileStream << nextWeeklyReset().resetTime.toLocalTime().toString() << "\n";
        fileStream << hasResetDaily << "\n";
        fileStream << hasResetWeekly;
    }
}

int DateChecker::daysTillWeeklyReset(QDateTime date)
{
    int newDate = 0;

    //Find how many days till the reset day desired which is Thursday 12 AM
    //my calculation is if we are before thursday then just find the amount
    //of days till thursday and if not then we need use use the difference
    //of the days and subtract by 7 leading us to the thursday in the future
    if(date.date().dayOfWeek() > 4)
    {
        newDate = 7 - static_cast<int>(qFabs(date.date().dayOfWeek() - 4));
    }
    else
    {
        newDate = static_cast<int>(qFabs(date.date().dayOfWeek() - 4));
    }

    int milliseconds = date.time().msecsSinceStartOfDay();
    //If its past reset time so anything past 12AM
    if(milliseconds != 0)
    {
        newDate -= 1;
    }

    return newDate;
}

void DateChecker::readFromFile()
{
    QFile file("ResetsAndTime.txt");

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream fileStream(&file);

        while(!fileStream.atEnd())
        {
            lastTimeOpened = QDateTime::fromString(fileStream.readLine());
            lastDailyResetTime = QDateTime::fromString(fileStream.readLine());
            lastWeeklyResetTime = QDateTime::fromString(fileStream.readLine());
            hasResetDaily = fileStream.readLine().toInt();
            hasResetWeekly = fileStream.readLine().toInt();
        }
    }

    QDate nextDaily = lastDailyResetTime.toUTC().date().addDays(1);
    QDate nextWeekly = lastWeeklyResetTime.toUTC().date();

    if(QDate::currentDate().day() > nextDaily.day())
    {
        hasResetDaily = false;
    }

    if(QDate::currentDate().day() > nextWeekly.day())
    {
        hasResetWeekly = false;
    }
}
