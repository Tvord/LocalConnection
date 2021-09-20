//
// Created by tokareva on 17.09.2021.
//

#ifndef DBUS_TEST_LOCALSERVER_H
#define DBUS_TEST_LOCALSERVER_H
#include <QObject>
#include <QThread>
#include <QLocalServer>
#include <QLocalSocket>

class LocalServer : public QThread {
Q_OBJECT
public:
    explicit LocalServer(QObject* parent = nullptr);
    ~LocalServer();

public slots:
    void stopIt();

private slots:
    void newIncomingConnection();
    void receiveData();

signals:
    void StopCalled();

private:
    QString uname;
    bool init{true};
    bool fStop{false};
    QLocalServer *server;
};

class LocalSocket : public QThread {
    Q_OBJECT
public:
    explicit LocalSocket(QObject* parent = nullptr);
    ~LocalSocket() override;

public slots:
    void stopIt();
    void setUsername(const QString& username);

private slots:
    void EvDisconnected();
    void EvConnected();
    void SendKeepalive();
    void SendUsername();
    void ReceiveData();
    void PreQuitActions();

signals:
    void StopCalled();
    void UsernameChanged();
    void callKeepalive();

private:
    QString uname;
    bool fStop{false};
    bool doKeepalive{false};
    QLocalSocket *sock;
    void run() override;
    void ConnectFun();
};
#endif //DBUS_TEST_LOCALSERVER_H
