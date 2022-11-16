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
    void createChat(User* u);
    void sendMessage();


};


#endif //LABPROG_CHAT_USER_H
