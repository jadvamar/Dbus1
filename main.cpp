#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QDBusConnection>
#include <QDBusMessage>
#include "dbusinterface.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
qmlRegisterType<DbusInterface>("com.example.dbus", 1, 0, "DbusInterface");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("DbusSenderApp", "Main");

    return app.exec();
}
