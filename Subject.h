//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_SUBJECT_H
#define LABPROG_CHAT_SUBJECT_H

#include "Observer.h"
#include "Message.h"

class Subject {
public:
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
    virtual void notifyObservers(Message msg) const = 0;

};

#endif //LABPROG_CHAT_SUBJECT_H
