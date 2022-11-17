//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include <string>
#include "User.h"

User::User() {
    using namespace std;
    cout << "Inserisci il nome dell'utente" << endl;
    cin >> this->name;
    this->myNotifier = new Notifier(this->name);
}

void User::createChat(User* u) {//TODO vedere se si può fare più bellino
    auto c = std::make_shared<Chat>();
    this->myChats.insert(std::make_pair(u->name, c));
    c->subscribe(this->myNotifier);
    u->myChats.insert(std::make_pair(this->name, c));
    c->subscribe(u->myNotifier);
}

void User::sendMessage() {
    std::string name = writeReceiverName();
    auto c = myChats.find(name)->second;
    Message* msg = new Message();
    msg->setSender(this->name);
    std::string txt = writeMessageText();
    msg->setText(txt);
    c->addMessage(*msg);
}

std::string User::writeReceiverName() {
    std::string name;
    std::cout << "Selezionare un destinatario: \n";
    std::cin >> name;
    return name;
}

std::string User::writeMessageText() {
    std::string txt;
    std::cout << "Inserire contenuto del messaggio: \n";
    std::cin.ignore();
    getline(std::cin, txt);
    return txt;
}
