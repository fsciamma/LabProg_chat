//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include "User.h"

User::User() {
    std::cout << "Inserisci il nome dell'utente:" << std::endl;
    std::cin >> this->name;
    this->myNotifier = new Notifier(this->name);
    this->BN = new badNotifier(4);
}

User::User(const std::string& name){
    this->name = name;
    this->myNotifier = new Notifier(name);
    this->BN = new badNotifier(4);
}

void User::createChat(User* u) {//TODO valutare se serve un metodo di appoggio che prenda in ingresso lo shared_ptr a Chat e faccia l'insert su User1->myChats della coppia User2->nome - Chat e il subscribe di User1->myNotifier alla Chat e faccia lo stesso su User2
    if(this->myChats.find(u->name) != this->myChats.end()){ //TODO creare test e mettere try/catch nel main
        throw std::runtime_error("Esiste già una chat con " + u->name);
    }
    auto c = std::make_shared<Chat>();
    this->myChats.insert(std::make_pair(u->name, c));
    c->subscribe(this->myNotifier);
    u->myChats.insert(std::make_pair(this->name, c));
    c->subscribe(u->myNotifier);
}

void User::createGroupChat(std::vector<User*> users, std::string groupName){ //TODO creare test e mettere try/catch nel main
    if(this->myChats.find(groupName) != this->myChats.end()){
        throw std::runtime_error("Hai gia' un gruppo chiamato " + groupName);
    }
    auto c = std::make_shared<GroupChat>(groupName);
    this->myChats.insert(std::make_pair(groupName, c));
    c->subscribe(this->myNotifier);
    c->subscribe(this->BN); //Usato solo per avere una seconda sottoclasse di Observer, per mettere in risalto il controllo tramite dynamic_cast
    for (auto u: users) {
        u->myChats.insert(std::make_pair(groupName, c));
        c->subscribe(u->myNotifier);
    }
}

void User::deleteChat(User* u){
    if(this->myChats.find(u->name) != this->myChats.end()){
        this->myChats.erase(u->name);
    }
}

void User::sendMessage(std::string txt, const std::string& _name) { //TODO creare test e mettere try/catch nel main
    if(myChats.find(_name) == myChats.end()){
        throw std::runtime_error("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message* msg = new Message(this->name, txt);
    c->addMessage(*msg);
    sleep(1);
}

void User::readChat(const std::string& chatName){
    try {
        auto chatNameMapped = this->myChats.find(chatName);
        chatNameMapped != this->myChats.end() ? chatNameMapped->second->readChatMessages() : throw std::runtime_error("Non esiste nessuna chat " + chatName); //TODO aggiungere metodo per testare il throw dell'eccezione
    } catch (std::out_of_range &o){
        std::cerr << "Out of range error: " << o.what() << std::endl;
    }
}

void User::readLastMessageFrom(const std::string& chatName) {
    try {
        auto chatNameMapped = this->myChats.find(chatName);
        chatNameMapped != this->myChats.end() ? chatNameMapped->second->readLastMessage() : throw std::runtime_error("Non esiste nessuna chat " + chatName); //TODO aggiungere metodo per testare il throw dell'eccezione
    } catch (std::out_of_range &o){
        std::cerr << "Out of range error: " << o.what() << std::endl;
    }
}

void User::leaveGroup(const std::string& groupName) {
    if(this->myChats.find(groupName) != this->myChats.end()){
        this->myChats.erase(groupName);
        std::cout << "Hai lasciato il gruppo " + groupName << std::endl;
    }
}
