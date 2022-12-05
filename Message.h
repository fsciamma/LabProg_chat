//
// Created by filip on 16/11/2022.
//

#ifndef LABPROG_CHAT_MESSAGE_H
#define LABPROG_CHAT_MESSAGE_H


#include <string>
#include <set>

class Message {
private:
    std::string sender;
    std::string receiver;
    std::string text;
    time_t myTime;
    std::set<std::string> read;

public:
    Message(std::string sender, std::string receiver, std::string text);

    ~Message(){}

    const std::string &getSender() const;
    const std::string &getReceiver() const;
    const std::string &getText() const;
    time_t getMyTime() const;
    bool isRead(const std::string &userName) const;
    void setRead(const std::string &userName);
};


#endif //LABPROG_CHAT_MESSAGE_H
