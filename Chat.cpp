//
// Created by filip on 15/11/2022.
//

#include "Chat.h"
#include "Notifier.h"

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
        if(Notifier* obsNot = dynamic_cast<Notifier*>(obs)) {
            if (obsNot->getName() != msg.getSender()) {
                obs->update(msg);
            }
        }
    }
}

void Chat::addMessage(Message msg) {
    this->messages.push_back(msg);
    notifyObservers(msg);
}

void Chat::readChatMessages() {
    if(this->messages.empty()){
        throw std::out_of_range("Non ci sono ancora messaggi");
    }
    for(auto msg: this->messages){
        char timestamp[40];
        time_t _t = msg.getMyTime();
        struct tm* localTime = localtime(&_t);
        strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
        std::cout << timestamp << " - " + msg.getSender() + " : " + msg.getText() << std::endl;
    }
}

void Chat::readLastMessage() {
    if(this->messages.empty()){
        throw std::out_of_range("Non ci sono ancora messaggi");
    }
    auto msg = this->messages.back();
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    char timestamp[40];
    strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
    std::cout << timestamp << " " + msg.getSender() + ": " + msg.getText() << std::endl;
}
