//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_CHAT_H
#define LABPROG_CHAT_CHAT_H


#include <vector>
#include <string>
#include <list>
#include "Subject.h"

class Chat : public Subject{
private:
    std::list<Observer*> readers;
    std::vector<Message> messages;

public:
    Chat();

    void subscribe(Observer *o) override;
    void unsubscribe(Observer *o) override;
    void notifyObservers(Message msg) const override;

    void addMessage(Message);
    void readChatMessages();
    void readLastMessage();
};


#endif //LABPROG_CHAT_CHAT_H
