//
// Created by filip on 22/11/2022.
//

#ifndef LABPROG_CHAT_BADNOTIFIER_H
#define LABPROG_CHAT_BADNOTIFIER_H


#include "Observer.h"

class badNotifier : public Observer{
private:
    int number;

public:
    badNotifier(int number);

    virtual ~badNotifier() override{}

    void update(Message& msg) override;
};


#endif //LABPROG_CHAT_BADNOTIFIER_H
