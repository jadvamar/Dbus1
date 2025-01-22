#include "dbusinterface.h"
#include <QDebug>

DbusInterface::DbusInterface(QObject *parent) : QObject(parent)
{
    if (QDBusConnection::sessionBus().isConnected()) {
        qDebug() << "Successfully connected to the D-Bus session bus.";
        QDBusConnection::sessionBus().registerService("org.example.MessageService1");
        QDBusConnection::sessionBus().registerObject(
            "/org/example/MessageService1",
            this,
            QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals
            );
    }
    else{
        qDebug() << "Failed to connect to the D-Bus session bus:"
                 << QDBusConnection::sessionBus().lastError().message();
    }
}

void DbusInterface::sendMessageToApp2(const QString &message)
{
    // Send message to App2
    QDBusMessage dbusMessage = QDBusMessage::createMethodCall(
        "org.example.MessageService2",
        "/org/example/MessageService2",
        "org.example.MessageService2",
        "receiveMessageFromApp1"
        );
    dbusMessage << message;

    QDBusMessage reply = QDBusConnection::sessionBus().call(dbusMessage);
    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Error sending message to App2:" << reply.errorMessage();
    }
}

void DbusInterface::receiveMessageFromApp2(const QString &message)
{
    qDebug() << "Message received from App2:" << message;
    emit messageReceivedFromApp2(message);
}
