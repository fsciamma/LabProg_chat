//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include "User.h"
#include "GroupChat.h"

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
    if(this->myChats.find(u->name) == this->myChats.end()) { //controlla che non ci sia già una chat con lo stesso utente
        auto c = std::make_shared<Chat>();
        this->myChats.insert(std::make_pair(u->name, c));
        c->subscribe(this->myNotifier);
        u->myChats.insert(std::make_pair(this->name, c));
        c->subscribe(u->myNotifier);
    } else {
        std::cerr << "Esiste gia' una chat con " + u->name << std::endl;
    }
}

void User::createGroupChat(std::vector<User*> users, std::string groupName){
    if(this->myChats.find(groupName) == this->myChats.end()) {
        auto c = std::make_shared<GroupChat>(groupName);
        this->myChats.insert(std::make_pair(groupName, c));
        c->subscribe(this->myNotifier);
        c->subscribe(this->BN); //Usato solo per avere una seconda sottoclasse di Observer, per mettere in risalto il controllo tramite dynamic_cast
        for (auto u: users) {
            u->myChats.insert(std::make_pair(groupName, c));
            c->subscribe(u->myNotifier);
        }
    } else {
        std::cerr << "Hai gia' un gruppo chiamato " + groupName << std::endl;
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

void User::sendMessage(std::string txt, std::string _name) {
    if(myChats.find(_name) != myChats.end()){
        auto c = myChats.find(_name)->second;
        Message* msg = new Message(this->name, txt);
        c->addMessage(*msg);
        sleep(1);
    }else{
        std::cerr << "Non e' stata trovata nessuna chat con " + _name << std::endl;
    }

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
    this->myChats.find(chatName)->second->readChatMessages();
}

void User::readLastMessageFrom(std::string chatName) {
    this->myChats.find(chatName)->second->readLastMessage();
}

void User::leaveGroup(std::string groupName) {
    if(this->myChats.find(groupName) != this->myChats.end()){
        this->myChats.erase(groupName);
        std::cout << "Hai lasciato il gruppo " + groupName << std::endl;
    }
}
