//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_NOTIFIER_H
#define LABPROG_CHAT_NOTIFIER_H


#include <string>
#include "Observer.h"

class Notifier : public Observer{
private:
    std::string name;

public:
    explicit Notifier(const std::string &name);

    ~Notifier() override;

    void update(Message& msg) override;
    std::string getName() override;

};


#endif //LABPROG_CHAT_NOTIFIER_H
