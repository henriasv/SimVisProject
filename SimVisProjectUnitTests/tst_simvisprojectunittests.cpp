#include <QString>
#include <QtTest>

class SimVisProjectUnitTests : public QObject
{
    Q_OBJECT

public:
    SimVisProjectUnitTests();

private Q_SLOTS:
    void testCase1();
};

SimVisProjectUnitTests::SimVisProjectUnitTests()
{
}

void SimVisProjectUnitTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SimVisProjectUnitTests)

#include "tst_simvisprojectunittests.moc"
