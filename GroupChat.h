//
// Created by filip on 22/11/2022.
//

#ifndef LABPROG_CHAT_GROUPCHAT_H
#define LABPROG_CHAT_GROUPCHAT_H


#include "Chat.h"

class GroupChat : public Chat{
private:
    std::string groupName;

public:
    GroupChat(std::string gn) : groupName(gn){}

    void readChatMessages() override;
    void readLastMessage() override;
};


#endif //LABPROG_CHAT_GROUPCHAT_H
