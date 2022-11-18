//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include "Chat.h"

Chat::Chat() {
    std::cout << "E' stata creata una chat" << std::endl; //TODO levare
}

void Chat::subscribe(Observer *o) {
    readers.push_back(o);
}

void Chat::unsubscribe(Observer *o) {
    readers.remove(o);
}

void Chat::notifyObservers(Message msg) const {
    for(auto obs: readers){
        //TODO potrei passare al notifier il nome del User a cui appartiene e fare un controllo su quello
        if(obs->getName() != msg.getSender()){ //TODO aggiungere controllo su sender
            obs->update(msg);
        }
    }
}

void Chat::addMessage(Message msg) {
    this->messages.push_back(msg);
    notifyObservers(msg);
}

void Chat::readChatMessages() {
    for(auto msg: this->messages){
        char time[20];
        time_t _t = msg.getMyTime();
        struct tm* localTime = localtime(&_t);
        strftime(time, 20, "%H:%M:%S", localTime);
        std::cout << time << " - " + msg.getSender() + " : " + msg.getText() + "\n";
    }
}
