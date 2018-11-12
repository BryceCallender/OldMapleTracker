#ifndef DATECHECKER_H
#define DATECHECKER_H

#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtMath>

struct ResetDate
{
    QString timeMessage;
    QString resetType;
    QDateTime resetTime;
};

class DateChecker
{
public:
    DateChecker();
    bool isDailyReset();
    bool isWeeklyReset();
    QString timeTillDailyReset();
    QString timeTillWeeklyReset();
    ResetDate nextDailyReset();
    ResetDate nextWeeklyReset();
    void writeToFile();
    int daysTillWeeklyReset(QDateTime date);
private:
    void readFromFile();
    ResetDate calcTimeTillReset(int days = 0, QString type = "Daily");
    bool hasResetDaily;
    bool hasResetWeekly;
    QDateTime lastTimeOpened;
    QDateTime lastDailyResetTime;
    QDateTime lastWeeklyResetTime;
    QTime midnight;
};

#endif // DATECHECKER_H
