//
// Created by filip on 22/11/2022.
//

#include "GroupChat.h"

void GroupChat::readChatMessages() {
    for(auto msg: this->messages){
        char timestamp[40];
        time_t _t = msg.getMyTime();
        struct tm* localTime = localtime(&_t);
        strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
        std::cout << timestamp << " - " + msg.getSender() + " @" + this->groupName + " : " + msg.getText() << std::endl;
    }
}

void GroupChat::readLastMessage() {
    auto msg = this->messages.back();
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    char timestamp[40];
    strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
    std::cout << timestamp << " " + msg.getSender() + " @" + this->groupName + ": " + msg.getText() << std::endl;
}
