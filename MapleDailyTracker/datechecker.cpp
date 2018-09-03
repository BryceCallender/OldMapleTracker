  #include "datechecker.h"

DateChecker::DateChecker()
{
    QTime resetTime(0,0);

    midnight.setHMS(23,59,59);

    readFromFile();

    dailyReset.setTime(resetTime);
    weeklyReset.setTime(resetTime);

    nextDailyReset();
    nextWeeklyReset();
}

bool DateChecker::isDailyReset()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    dailyReset.setDate(currentTime.date());
    dailyReset.date() = dailyReset.date().addDays(1);

    //If we went pass the daily reset time and have not reset yet then
    //lets reset
    if(currentTime.toUTC().secsTo(dailyReset) < 0 && !hasResetDaily)
    {
        hasResetDaily = true;
        return hasResetDaily;
    }
    hasResetDaily = false;
    return hasResetDaily;
}

bool DateChecker::isWeeklyReset()
{
    QDateTime currentTime(QDateTime::currentDateTime());

    //If we went pass the weekly reset time and have not reset yet then
    //lets reset and make sure it is a thursday because it resets thursday at midnight UTC
    if(currentTime.toUTC().secsTo(dailyReset) < 0 && !hasResetWeekly)
    {
        hasResetDaily = true;
        return hasResetDaily;
    }
    hasResetDaily = false;
    return hasResetDaily;
}

QDateTime DateChecker::nextDailyReset()
{
    return calcTimeTillReset();
}

QDateTime DateChecker::nextWeeklyReset()
{
    QDateTime currentTime = QDateTime::currentDateTimeUtc();

    //Set time to UTC so i can be relating this for everytime
    //zone without having to worry about DST
    currentTime.setTimeSpec(Qt::UTC);

    //Find how many days till the reset day desired which is Thursday 12 AM
    int newDate = 7 - static_cast<int>(qFabs(currentTime.date().dayOfWeek() - 4));

    int milliseconds = currentTime.time().msecsSinceStartOfDay();

    //If its past reset time so anything past 12AM
    if(milliseconds != 0)
    {
        newDate -= 1;
    }

    return calcTimeTillReset(newDate);
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
            hasResetDaily = fileStream.readLine().toInt();
            hasResetWeekly = fileStream.readLine().toInt();
        }
    }
}

QDateTime DateChecker::calcTimeTillReset(int days)
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

    qDebug() << message;

    //find how many seconds have elapsed since beginning of day for math reason
    int seconds = QTime(0,0,0).secsTo(timeTillReset);

    //update the time and date accordingly
    QTime updatedTime = currentTime.time().addSecs(seconds);
    QDate updatedDate = currentTime.date().addDays(1);

    QDateTime nextReset(updatedDate,updatedTime);
    nextReset.setTimeSpec(Qt::UTC);

    qDebug() << nextReset.toLocalTime().toString("h:m:s AP");

    return nextReset;
}

void DateChecker::writeToFile()
{
    QFile file("ResetsAndTime.txt");

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream fileStream(&file);

        fileStream << QDateTime::currentDateTime().toString() << "\n";
        fileStream << nextDailyReset().toLocalTime().toString() << "\n";
        fileStream << nextWeeklyReset().toLocalTime().toString() << "\n";
        fileStream << hasResetDaily << "\n";
        fileStream << hasResetWeekly;
    }
}
