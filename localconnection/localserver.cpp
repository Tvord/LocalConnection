//
// Created by tokareva on 17.09.2021.
//

#include "localconnection.h"
#include <QTimer>
#include <QEventLoop>

//! Server needs to be run from PSA daemon
//! Features: Receive username from clients (Operative journal instances) and use it on database insert
//! If run before journals (likely) - listen and wait until username passed in
//! If run after journals (service restart) - ask client (starts from first) about current username
//! On connection break (unlikely) - ask after reconnect

LocalServer::LocalServer(QObject *parent) {
    //! Also receive current username
    server = new QLocalServer(this);
    if (!server->listen("PSAServer4")) {
        qDebug() << "Something went wrong with listening server";
        server->close();
        return;
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(newIncomingConnection()));

    qDebug() << "Server created!";
}

LocalServer::~LocalServer() {
    server->close();
    delete server;
}

void LocalServer::stopIt() {
    fStop = true;
    emit StopCalled();
}

void LocalServer::newIncomingConnection() {
    qDebug() << "New incoming connection!";
    auto socket = server->nextPendingConnection();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    //socket->write("You are connected to server!");
    if (init) {
        qDebug() << "Sending init flag!";
        socket->write("I");
    }
}

void LocalServer::receiveData() {
    auto socket = (QLocalSocket*)sender();
    auto data = socket->readAll();
    switch (data.at(0)) {
        case 'i':
            init = false; break; //! Socket just created and needs in initialisation
        case 'q': ; break; //! Periodic query
        case 'w': uname = QString(data.mid(1,data.length() - 1));
                qDebug() << "Received username: " << uname;
                if (uname.isEmpty())
                    socket->write("E");
                else
                    socket->write("W");
                break; //! Receive new operator name
        case 'a': socket->write("A"); break; //! Keepalive
        default: qDebug() << "Unsupported query received: " << data;
    }
    qDebug() << "Received query: " << data;
}
