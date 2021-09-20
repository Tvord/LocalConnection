//
// Created by tokareva on 17.09.2021.
//

#include <QCoreApplication>
#include <iostream>
#include "../../localconnection/localconnection.h"
#include "../ConsoleReader/ConsoleReader.h"

int main(int argc, char** argv) {
    QCoreApplication a(argc,argv);
    LocalSocket receiver;
    receiver.start();

    std::string uname;
    Console cons;
    QCoreApplication::connect(&cons, SIGNAL(dataReceived(QString)), &receiver, SLOT(setUsername(const QString &)));
    cons.run();
    return a.exec();
}