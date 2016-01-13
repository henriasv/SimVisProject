#include <QString>
#include <QtTest>
#include "../SimVisProject/ghostbox.h"

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
    GhostBox ghostBox(0, 1, 0, 1, 0, 1, 0, 0.7, 0, 0.7, 0, 0.7);
    ghostBox.addParticle(QVector3D(0.5, 0.5, 0.5));
    QVERIFY2(ghostBox.numParticles() == 1, "Failure");
    ghostBox.addParticle(QVector3D(0.01, 0.01, 0.01));
    QVERIFY2(ghostBox.numParticles() == 9, "Failure");
    ghostBox.addParticle(QVector3D(0.5, 0.2, 0.2));
    QVERIFY2(ghostBox.numParticles() == 13, "Failure");
    QVERIFY2(!ghostBox.addParticle(QVector3D(0.8, 0, 0)), "Was allowed to add particle from outside of simulation box");
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SimVisProjectUnitTests)

#include "tst_simvisprojectunittests.moc"
