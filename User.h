//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_USER_H
#define LABPROG_CHAT_USER_H


#include <map>
#include <memory>
#include "Notifier.h"
#include "GroupChat.h"

class User {
private:
    std::string name;
    std::map<std::string, std::shared_ptr<Chat>> myChats;
    std::map<std::string, Notifier*> myNotifiers;

public:
    User();
    explicit User(const std::string& name);
    virtual ~User(){}

    void chatRegister() const;
    void getUnreadMessages(std::string chat) const;
    void getUnreadMessages() const;
    void readUnreadMessages(std::string chat);

    //Metodi per mappare nomi e shared_ptr
    void mapChatToName(const std::string& chatName, std::shared_ptr<Chat> c);
    void unmapChatToName(const std::string& chatName);

    //Metodi Chat
    void createChat(User* u);
    void readChat(const std::string& chatName) const;
    void readLastMessageFrom(const std::string& chatName) const;

    //Metodi GroupChat
    void createGroupChat(const std::vector<User*>& users, const std::string& groupName);
    void addUserToGroupChat(User* u, const std::string& groupName);
    void kickUserFromGroupChat(User* u, const std::string& groupName);
    void leaveGroup(const std::string& groupName);

    //Metodi Message
    void sendMessage(std::string txt, const std::string& _name = "Filippo");
};


#endif //LABPROG_CHAT_USER_H
