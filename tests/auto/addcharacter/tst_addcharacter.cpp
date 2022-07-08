#include <QTest>
#include <QCoreApplication>

class Tst_AddCharacter : public QObject
{
    Q_OBJECT
public:
    Tst_AddCharacter();

private slots:
};

Tst_AddCharacter::Tst_AddCharacter()
{

}

QTEST_MAIN(Tst_AddCharacter)
#include "tst_addcharacter.moc"
