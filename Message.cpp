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

void Message::setSender(const std::string &sender) {
    Message::sender = sender;
}

void Message::setText(const std::string &text) {
    Message::text = text;
}
