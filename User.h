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
    virtual ~User(){}

    void createChat(User* u);
    void createGroupChat(std::vector<User*> users, std::string groupName);
    void deleteChat(User* u);
    //void sendMessage();
    void sendMessage(std::string txt, std::string _name = "Filippo");
    //std::string writeReceiverName();
    //std::string writeMessageText();
    //void readChat();
    void readChat(std::string chatName);
    void readLastMessageFrom(std::string chatName);

};


#endif //LABPROG_CHAT_USER_H
