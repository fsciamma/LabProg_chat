//
// Created by filip on 16/11/2022.
//

#include "Message.h"

Message::Message(std::string sender, std::string text) : sender(sender), text(text){
    time(&myTime);
}

const std::string &Message::getSender() const {
    return sender;
}

const std::string &Message::getText() const {
    return text;
}

time_t Message::getMyTime() const {
    return myTime;
}
