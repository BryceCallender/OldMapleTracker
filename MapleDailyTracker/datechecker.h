#ifndef DATECHECKER_H
#define DATECHECKER_H

#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtMath>

class DateChecker
{
public:
    DateChecker();
    bool isDailyReset();
    bool isWeeklyReset();
    QDateTime timeTillDailyReset();
    QDateTime timeTillWeeklyReset();
    QDateTime nextDailyReset();
    QDateTime nextWeeklyReset();
    void writeToFile();
private:
    const int thursday = 4;
    void readFromFile();
    QDateTime calcTimeTillReset(int days = 0);
    bool hasResetDaily;
    bool hasResetWeekly;
    QDateTime lastTimeOpened;
    QDateTime lastDailyResetTime;
    QDateTime lastWeeklyResetTime;
    QDateTime dailyReset;
    QDateTime weeklyReset;
    QTime midnight;
};

#endif // DATECHECKER_H
