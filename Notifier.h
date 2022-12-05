//
// Created by filip on 15/11/2022.
//

#ifndef LABPROG_CHAT_NOTIFIER_H
#define LABPROG_CHAT_NOTIFIER_H


#include <string>
#include <memory>
#include "Observer.h"
#include "GroupChat.h"

class Notifier : public Observer{
private:
    std::string name;
    std::shared_ptr<Chat> c;

public:
    explicit Notifier(const std::string &name, std::shared_ptr<Chat> c);

    virtual ~Notifier() override{}

    void update(Message& msg) override;
    std::string getName();

    int getUnreadNotifications();

};


#endif //LABPROG_CHAT_NOTIFIER_H
