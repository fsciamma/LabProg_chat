//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include "Notifier.h"

Notifier::Notifier(const std::string &name){
    this->name = name;
}

void Notifier::update(Message& msg) {
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    char timestamp[40];
    strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);

    std::cout << "Ehi " + this->name + ", hai ricevuto un messaggio!" << std::endl;
}

std::string Notifier::getName() {
    return name;
}

