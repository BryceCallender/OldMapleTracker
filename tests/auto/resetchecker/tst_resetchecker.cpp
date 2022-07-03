#include <QTest>

// add necessary includes here

class Tst_ResetChecker : public QObject
{
    Q_OBJECT

public:
    Tst_ResetChecker();
private slots:
};

Tst_ResetChecker::Tst_ResetChecker()
{

}

QTEST_APPLESS_MAIN(Tst_ResetChecker)
#include "tst_resetchecker.moc"
