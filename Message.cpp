//
// Created by filip on 16/11/2022.
//

#include "Message.h"

const std::string &Message::getSender() const {
    return sender;
}

const std::string &Message::getText() const {
    return text;
}

Message::Message(std::string sender, std::string text) : sender(sender), text(text){
    time(&myTime);
}

time_t Message::getMyTime() const {
    return myTime;
}
