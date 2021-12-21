#ifndef TIMEDATA_H
#define TIMEDATA_H

#include <QString>

class TimeData
{
public:
    TimeData();
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
    void setTimeData(int hour = 0, int minute = 0, int second = 0);
    QString toString() const;
private:
    int hour;
    int minute;
    int second;
};

#endif // TIMEDATA_H
