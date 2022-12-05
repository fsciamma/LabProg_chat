//
// Created by filip on 22/11/2022.
//

#ifndef LABPROG_CHAT_GROUPCHAT_H
#define LABPROG_CHAT_GROUPCHAT_H


#include "Chat.h"

class GroupChat : public Chat{
private:
    std::string groupName;
    //TODO potrei aggiungere un std::vector di User che sono admin del gruppo...?

public:
    explicit GroupChat(std::string gn) : groupName(gn){}
    ~GroupChat(){}

    const std::string &getGroupName() const;

    void readChatMessages(std::string userName) override;
    void readLastMessage(std::string userName) override;
    void showUnreadMessages(std::string userName) override;
};


#endif //LABPROG_CHAT_GROUPCHAT_H
