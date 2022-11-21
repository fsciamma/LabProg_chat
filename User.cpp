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
    //TODO mettere un controllo per verificare che non esista già una chat con lo stesso nome
    auto c = std::make_shared<Chat>();
    this->myChats.insert(std::make_pair(u->name, c));
    c->subscribe(this->myNotifier);
    u->myChats.insert(std::make_pair(this->name, c));
    c->subscribe(u->myNotifier);
}

void User::sendMessage() { //TODO forse non dovrebbe lanciare un'eccezione, ma solo gestire con un if else...
    std::string _name = writeReceiverName();
    if(myChats.find(_name) == myChats.end()){
        throw std::invalid_argument("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message* msg = new Message(this->name, writeMessageText());
    c->addMessage(*msg);
}

void User::sendMessage(std::string txt, std::string _name) {
    if(myChats.find(_name) == myChats.end()){
        throw std::invalid_argument("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message* msg = new Message(this->name, txt);
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

void User::readChat() {
    std::string chatName;
    std::cout << "Quale chat vuoi leggere? \n";
    std::cin.ignore();//TODO fixare i problemi che ci sono con cin.ignore
    getline(std::cin, chatName);
    this->myChats.find(chatName)->second->readChatMessages();
}

void User::readLastMessageFrom(std::string chatName) {
    this->myChats.find(chatName)->second->readLastMessage();
}
