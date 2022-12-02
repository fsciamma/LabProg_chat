//
// Created by filip on 16/11/2022.
//

#include "Message.h"

Message::Message(std::string sender, std::string receiver, std::string text) : sender(sender), receiver(receiver), text(text){
    time(&myTime);
}

const std::string &Message::getSender() const {
    return sender;
}

const std::string &Message::getReceiver() const {
    return receiver;
}

const std::string &Message::getText() const {
    return text;
}

time_t Message::getMyTime() const {
    return myTime;
}
