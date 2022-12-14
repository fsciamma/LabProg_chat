//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_CHAT_H
#define LABPROG_CHAT_CHAT_H


#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Subject.h"

class Chat : public Subject{
protected:
    std::list<Observer*> readers;
    std::vector<Message> messages;

public:
    Chat();
    ~Chat() override{}

    void subscribe(Observer *o) override;
    void unsubscribe(Observer *o) override;
    void notifyObservers(Message msg) const override;

    void addMessage(Message msg);
    int getUnreadMessages(const std::string &userName) const;
    virtual void readChatMessages(const std::string &userName);
    virtual void readLastMessage(const std::string &userName);
    virtual void showUnreadMessages(const std::string &userName);
};


#endif //LABPROG_CHAT_CHAT_H
