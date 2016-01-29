#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "figure.h"
#include "linegraph.h"


#include "mysimulator.h"
int main(int argc, char *argv[])
{
    if (argc > 0)
    qmlRegisterType<MySimulator>("MySimulator", 1, 0, "MySimulator");
    qmlRegisterType<Figure>("QMLPlot", 1,0,"Figure");
    qmlRegisterType<LineGraph>("QMLPlot", 1,0,"LineGraph");
    qmlRegisterType<LineGraphDataSource>("QMLPlot", 1,0,"LineGraphDataSource");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

