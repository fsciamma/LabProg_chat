//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_USER_H
#define LABPROG_CHAT_USER_H


#include <map>
#include <memory>
#include "Notifier.h"
#include "Chat.h"

class User {
private:
    std::string name;
    std::map<std::string, std::shared_ptr<Chat>> myChats;
    Notifier* myNotifier;

public:
    User();
    explicit User(std::string name);
    void createChat(User* u);
    void sendMessage();
    void sendMessage(std::string _name, std::string txt);
    std::string writeReceiverName();
    std::string writeMessageText();
    void readChat();

};


#endif //LABPROG_CHAT_USER_H
