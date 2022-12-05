//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include "Notifier.h"

Notifier::Notifier(const std::string &name, std::shared_ptr<Chat> c): name(name), c(c){}

void Notifier::update(Message& msg) {
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    char timestamp[40];
    strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);

    if(this->name == msg.getReceiver()) { //in questo caso è una chat tra due utenti
        std::cout << "Ehi " + this->name + ", hai ricevuto un messaggio da " + msg.getSender() + "! Hai " << getUnreadNotifications() << " non letti in questa chat." << std::endl;
    } else { //in questo caso è una chat di gruppo
        std::cout << "Ehi " + this->name + ", hai ricevuto un messaggio da " + msg.getSender() + " @" + msg.getReceiver() + "! Hai " << getUnreadNotifications() << " non letti in questa chat di gruppo." << std::endl;
    }
}

const std::string &Notifier::getName() const {
    return name;
}

int Notifier::getUnreadNotifications() {
    return this->c->getUnreadMessages(this->name);
}

