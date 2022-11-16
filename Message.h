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

public:
    const std::string &getSender() const;
    const std::string &getText() const;

    void setText(const std::string &text);
    void setSender(const std::string &sender);
};


#endif //LABPROG_CHAT_MESSAGE_H
