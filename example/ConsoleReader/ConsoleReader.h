//
// Created by tokareva on 20.09.2021.
//

#ifndef DBUS_TEST_CONSOLEREADER_H
#define DBUS_TEST_CONSOLEREADER_H

#include <QObject>
#include <QSocketNotifier>
#include <iostream>

class Console : public QObject
{
Q_OBJECT;

public:
    Console();

    void run();

signals:
    void quit();
    void dataReceived(QString data);

private:
    QSocketNotifier *m_notifier;

private slots:
    void readCommand();
};

inline Console::Console()
{
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
}
#endif //DBUS_TEST_CONSOLEREADER_H
