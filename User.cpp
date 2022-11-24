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

User::User(std::string name){
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

/*
void User::sendMessage() { //TODO forse non dovrebbe lanciare un'eccezione, ma solo gestire con un if else...
    std::string _name = writeReceiverName();
    if(myChats.find(_name) == myChats.end()){
        throw std::invalid_argument("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message* msg = new Message(this->name, writeMessageText());
    c->addMessage(*msg);
}
 */

void User::sendMessage(std::string txt, std::string _name) { //TODO creare test e mettere try/catch nel main
    if(myChats.find(_name) == myChats.end()){
        throw std::runtime_error("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message* msg = new Message(this->name, txt);
    c->addMessage(*msg);
    sleep(1);
}
/*
std::string User::writeReceiverName() {
    std::string name;
    std::cout << "Selezionare un destinatario:" << std::endl;
    std::cin >> name;
    return name;
}

std::string User::writeMessageText() {
    std::string txt;
    std::cout << "Inserire contenuto del messaggio:" << std::endl;
    //std::cin.ignore();
    getline(std::cin, txt);
    return txt;
}

void User::readChat() {
    std::string chatName;
    std::cout << "Quale chat vuoi leggere?" << std::endl;
    //std::cin.ignore();//TODO fixare i problemi che ci sono con cin.ignore
    getline(std::cin, chatName);
    this->myChats.find(chatName)->second->readChatMessages();
}
 */

void User::readChat(std::string chatName){
    try {
        this->myChats.find(chatName)->second->readChatMessages();
    } catch (std::out_of_range &o){
        std::cerr << "Out of range error: " << o.what() << std::endl;
    }
}

void User::readLastMessageFrom(std::string chatName) {
    try { //TODO aggiungere un controllo sull'esistenza o meno della Chat con chatName
        this->myChats.find(chatName)->second->readLastMessage();
    } catch (std::out_of_range &o){
        std::cerr << "Out of range error: " << o.what() << std::endl;
    }
}

void User::leaveGroup(std::string groupName) {
    if(this->myChats.find(groupName) != this->myChats.end()){
        this->myChats.erase(groupName);
        std::cout << "Hai lasciato il gruppo " + groupName << std::endl;
    }
}
