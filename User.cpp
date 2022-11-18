//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include <string>
#include "User.h"

User::User() {
    std::cout << "Inserisci il nome dell'utente:\n";
    std::cin >> this->name;
    this->myNotifier = new Notifier(this->name);
}

User::User(std::string name){
    this->name = name;
    this->myNotifier = new Notifier(name);
}

void User::createChat(User* u) {//TODO valutare se serve un metodo di appoggio che prenda in ingresso lo shared_ptr a Chat e faccia l'insert su User1->myChats della coppia User2->nome - Chat e il subscribe di User1->myNotifier alla Chat e faccia lo stesso su User2
    auto c = std::make_shared<Chat>();
    this->myChats.insert(std::make_pair(u->name, c));
    c->subscribe(this->myNotifier);
    u->myChats.insert(std::make_pair(this->name, c));
    c->subscribe(u->myNotifier);
}

void User::sendMessage() {
    //TODO aggiungere un'eccezione che viene lanciata se la persona a cui si vuole inviare un messaggio non figura tra quelle salvate in myChats
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
