#include <QTest>

#include "resetchecker.h"

class Tst_ResetChecker : public QObject
{
    Q_OBJECT

public:
    Tst_ResetChecker();
private slots:
    void test();
private:
    ResetChecker resetChecker;
};

Tst_ResetChecker::Tst_ResetChecker()
{

}

void Tst_ResetChecker::test()
{

}

QTEST_APPLESS_MAIN(Tst_ResetChecker)
#include "tst_resetchecker.moc"
