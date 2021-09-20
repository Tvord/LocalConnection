//
// Created by tokareva on 17.09.2021.
//

#include "localconnection.h"
#include <QTimer>
#include <QEventLoop>

LocalSocket::LocalSocket(QObject *parent) : QThread(parent) {
    sock = new QLocalSocket(this);
    ConnectFun();
}

LocalSocket::~LocalSocket() {
    sock->close();

    delete sock;
}

void LocalSocket::run() {
    QTimer tim;
    QEventLoop lp;
    tim.setInterval(1000);
    connect(&tim, SIGNAL(timeout()), &lp, SLOT(quit()));
    //connect(this, SIGNAL(StopCalled()), &lp, SLOT(quit()));
    connect(sock, SIGNAL(disconnected()), &lp, SLOT(quit()));
    connect(sock, SIGNAL(connected()), &lp, SLOT(quit()));
    //connect(sock, SIGNAL(readyRead()), &lp, SLOT(quit()));
    forever {
        if (fStop) break;
        if (doKeepalive) {
            emit callKeepalive();
        }
        tim.start();
        lp.exec();
    };
}

void LocalSocket::stopIt() {
    fStop = true;
    emit StopCalled();
}

void LocalSocket::EvDisconnected() {
    qDebug() << "Disconnected!";
    doKeepalive = false;
}

void LocalSocket::EvConnected() {
    qDebug() << "Connected!";
    doKeepalive = true;
}

void LocalSocket::ConnectFun() {
    connect(sock, SIGNAL(connected()), this, SLOT(EvConnected()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(EvDisconnected()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(ReceiveData()));
    connect(this, SIGNAL(UsernameChanged()), this, SLOT(SendUsername()));
    connect(this, SIGNAL(callKeepalive()), this, SLOT(SendKeepalive()));
    connect(this, SIGNAL(StopCalled()), this, SLOT(PreQuitActions()));
    sock->connectToServer("PSAServer4");
}

void LocalSocket::ReceiveData() {
    auto data = sock->readAll();
    qDebug() << data;
    switch (data[0]) {
        case 'A': qDebug() << "Server: Keepalive answer"; break; //! Keepalive
        case 'I': sock->write("i"); qDebug() << "Server: New connection found"; SendUsername(); break; //! Initial
        case 'W': qDebug() << "Server: username stored successfully"; break; //! Write username
        case 'E': qDebug() << "Server: Error while parsing username"; break;
        default: qDebug() << "Received unsupported query from server: " << data;
    }
}

void LocalSocket::SendUsername() {
    sock->write(QString("w%1").arg(uname).toLocal8Bit());
}

void LocalSocket::setUsername(const QString &username) {
    uname = username;
    emit UsernameChanged();
}

void LocalSocket::SendKeepalive() {
    qDebug() << "Sending keepalive...";
    sock->write("a");
}

void LocalSocket::PreQuitActions() {
    fStop = true;
    sock->disconnectFromServer();
}
