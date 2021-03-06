//
// Created by tokareva on 20.09.2021.
//

#include <iostream>
#include "ConsoleReader.h"

void Console::run()
{
    std::cout << "First message" << std::endl;
    std::cout << "> " << std::flush;
    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readCommand()));
}

void Console::readCommand()
{
    std::string line;
    std::getline(std::cin, line);
    if (std::cin.eof() || line == "quit") {
        std::cout << "Good bye!" << std::endl;
        emit quit();
    } else {

        std::cout << "Echo: " << line << std::endl;
        std::cout << "> " << std::flush;
        emit dataReceived(QString::fromStdString(line));
    }
}