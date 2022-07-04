#include <QDateTime>
#include <QTest>

#include "resetchecker.h"

class Tst_ResetChecker : public QObject
{
    Q_OBJECT

public:
    Tst_ResetChecker();

private slots:
    void testDailyResetTimer();
    void testMonWeeklyResetTimer();
    void testWedWeeklyResetTimer();
    void hasReset_data();
    void hasReset();
private:
    ResetChecker resetChecker;
};

Tst_ResetChecker::Tst_ResetChecker()
{

}


void Tst_ResetChecker::testDailyResetTimer()
{

}

void Tst_ResetChecker::testMonWeeklyResetTimer()
{

}

void Tst_ResetChecker::testWedWeeklyResetTimer()
{

}

void Tst_ResetChecker::hasReset_data()
{
    QTest::addColumn<bool>("reset");
    QTest::addColumn<bool>("result");

    QDateTime currentDateTime(QDate(2022, 7, 3), QTime(15, 0, 0), Qt::TimeSpec::LocalTime);
    QDateTime currentCloseDateTime(QDate(2022, 7, 3), QTime(23,59,59), Qt::TimeSpec::UTC);
    QDateTime utcTime = currentDateTime.toUTC();

    //Date is on date of the reset and the time is the time remaining to get there
    QDateTime dailyResetTime(QDate(2022, 7, 4), QTime(2, 0, 0), Qt::TimeSpec::UTC);
    QDateTime rightOnReset(QDate(2022, 7, 4), QTime(0, 0, 0), Qt::TimeSpec::UTC);

    QDateTime deltaBeforeReset(QDate(2022, 7, 4), QTime(0, 0, -2), Qt::TimeSpec::UTC);
    QDateTime deltaAfterReset(QDate(2022, 7, 4), QTime(0, 0, 2), Qt::TimeSpec::UTC);
    QDateTime rightBeforeReset(QDate(2022, 7, 4), QTime(0, 0, -10), Qt::TimeSpec::UTC);
    QDateTime rightAfterReset(QDate(2022, 7, 4), QTime(0, 0, 10), Qt::TimeSpec::UTC);


    QTest::newRow("too far before reset") << resetChecker.hasReset(rightBeforeReset.addSecs(-10), utcTime) << false;
    QTest::newRow("before reset") << resetChecker.hasReset(dailyResetTime, utcTime) << false;
    QTest::newRow("right before reset") << resetChecker.hasReset(rightBeforeReset, utcTime) << false;
    QTest::newRow("delta before reset") << resetChecker.hasReset(deltaBeforeReset, currentCloseDateTime.addSecs(-1)) << false;
    QTest::newRow("right at reset") << resetChecker.hasReset(rightOnReset, currentCloseDateTime.addSecs(1)) << true;
    QTest::newRow("delta after reset") << resetChecker.hasReset(deltaAfterReset, currentCloseDateTime.addSecs(2)) << true;
    QTest::newRow("a bit after reset") << resetChecker.hasReset(rightAfterReset, utcTime) << false;
    QTest::newRow("too far after reset") << resetChecker.hasReset(rightAfterReset.addSecs(10), utcTime) << false;
}

void Tst_ResetChecker::hasReset()
{
    QFETCH(bool, reset);
    QFETCH(bool, result);

    QCOMPARE(reset, result);
}

QTEST_APPLESS_MAIN(Tst_ResetChecker)
#include "tst_resetchecker.moc"
