//
// Created by filip on 15/11/2022.
//

#include <iostream>
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
    std::string name;
    std::cout << "Selezionare un destinatario:" << std::endl;
    std::cin >> name;
    auto c = myChats.find(name)->second;
    Message* msg = new Message();
    msg->setSender(this->name);
    std::string txt;
    std::cout << "Inserire contenuto del messaggio:" << std::endl;
    //FIXME quando il messaggio contiene più parole viene salvata solo la prima
    std::cin >> txt;
    msg->setText(txt);
    c->addMessage(*msg);
}
