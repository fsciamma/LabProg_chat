//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_USER_H
#define LABPROG_CHAT_USER_H


#include <map>
#include <memory>
#include "Notifier.h"
#include "GroupChat.h"
#include "badNotifier.h"

class User {
private:
    std::string name;
    std::map<std::string, std::shared_ptr<Chat>> myChats;
    Notifier* myNotifier; //TODO devo mettere un vector<Observer*>?
    badNotifier* BN;

public:
    User();
    explicit User(const std::string& name);
    virtual ~User(){}

    void mapChatToName(const std::string& chatName, std::shared_ptr<Chat> c);
    void unmapChatToName(const std::string& chatName);

    void createChat(User* u);
    void createGroupChat(const std::vector<User*>& users, const std::string& groupName);
    void addUserToGroupChat(const std::string& groupName, User* u);
    void kickUserFromGroupChat(const std::string& groupName, User* u);
    void sendMessage(std::string txt, const std::string& _name = "Filippo");
    void readChat(const std::string& chatName);
    void readLastMessageFrom(const std::string& chatName);
    void leaveGroup(const std::string& groupName);

};


#endif //LABPROG_CHAT_USER_H
