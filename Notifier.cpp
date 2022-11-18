//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include "Notifier.h"

Notifier::Notifier(const std::string &name){
    this->name = name;
}

void Notifier::update(Message msg) {
    char time[20];
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    strftime(time, 20, "%H:%M:%S", localTime);
    char date[20];
    strftime(date, 20, "%d-%m-%Y", localTime);

    std::cout << "Ehi " + this->name + ", hai ricevuto un messaggio!\nAlle " + time + " del " + date + ", " + msg.getSender() + " ha scritto: " + msg.getText() << std::endl;
}

std::string Notifier::getName() {
    return name;
}

Notifier::~Notifier() {

}

