//
// Created by filip on 16/11/2022.
//

#include "Message.h"

Message::Message(std::string sender, std::string receiver, std::string text) : sender(sender), receiver(receiver), text(text){
    read.insert(sender); //il nome del mittente viene subito salvato tra coloro che hanno letto il messaggio
    time(&myTime);
}

const std::string &Message::getSender() const {
    return sender;
}

const std::string &Message::getReceiver() const {
    return receiver;
}

const std::string &Message::getText() const {
    return text;
}

time_t Message::getMyTime() const {
    return myTime;
}

bool Message::isRead(const std::string &userName) const {
    if(this->read.find(userName) != this->read.end()){
        return true;
    }
    return false;
}

void Message::setRead(const std::string &userName) {
    this->read.insert(userName);
}
