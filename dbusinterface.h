#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H

#include <QObject>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>

class DbusInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.example.MessageService1")

public:
    explicit DbusInterface(QObject *parent = nullptr);
    Q_INVOKABLE void sendMessageToApp2(const QString &message);

signals:
    void messageReceivedFromApp2(const QString &message);

public slots:
    void receiveMessageFromApp2(const QString &message);
};

#endif // DBUSINTERFACE_H
