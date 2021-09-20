//
// Created by tokareva on 17.09.2021.
//
#include <QCoreApplication>
#include "../../localconnection/localconnection.h"
#include <iostream>
#include "../ConsoleReader/ConsoleReader.h"
#include <QDebug>

int main(int argc, char** argv)
{
    setenv("DISPLAY", "localhost:10.0", true);
    QCoreApplication a(argc,argv);
    LocalServer sender;

//    AdaptorObject aObject(new QObject());
//    if( ! QDBusConnection::sessionBus().registerObject("/", new QObject())){
//        qDebug() << "Can't register object";
//        exit(1);
//    }
//    if (!QDBusConnection::sessionBus().registerService("org.BR.psatoolkit.systemuser")) {
//        qDebug() << QDBusConnection::sessionBus().lastError().message();
//        //exit(1);
//    } else { qDebug() << "Registered!";}
    int b;
    Console cons;
    cons.run();
    QCoreApplication::connect(&cons, SIGNAL(quit()), &a, SLOT(quit()));
    return a.exec();
}