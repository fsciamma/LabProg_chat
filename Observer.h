//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_OBSERVER_H
#define LABPROG_CHAT_OBSERVER_H

#include "Message.h"

class Observer {
public:
    virtual ~Observer(){}

    virtual void update(Message& msg) = 0;
    virtual std::string getName() = 0;
};

#endif //LABPROG_CHAT_OBSERVER_H
