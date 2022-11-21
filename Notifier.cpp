//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include "Notifier.h"

Notifier::Notifier(const std::string &name){
    this->name = name;
}

Notifier::~Notifier() {

}

void Notifier::update(Message& msg) {
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    char timestamp[40];
    strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);

    std::cout << "Ehi " + this->name + ", hai ricevuto un messaggio!\n" << std::endl;// + timestamp + " " + msg.getSender() + ": " + msg.getText() << std::endl;
    //TODO forse dovrei mettere la parte inerente al messaggio in Chat...
}

std::string Notifier::getName() {
    return name;
}

