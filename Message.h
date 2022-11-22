//
// Created by filip on 16/11/2022.
//

#ifndef LABPROG_CHAT_MESSAGE_H
#define LABPROG_CHAT_MESSAGE_H


#include <string>

class Message {
private:
    std::string sender;
    std::string text;
    time_t myTime;
    //TODO aggiungere un boolean read?

public:
    Message(std::string sender, std::string text);

    ~Message(){}

    const std::string &getSender() const;
    const std::string &getText() const;

    time_t getMyTime() const;
};


#endif //LABPROG_CHAT_MESSAGE_H
