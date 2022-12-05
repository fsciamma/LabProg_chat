//
// Created by filip on 15/11/2022.
//

#include <iostream>
#include <string>
#include <utility>
#include <unistd.h>
#include "User.h"

User::User() { //TODO valutare se togliere
    std::cout << "Inserisci il nome dell'utente:" << std::endl;
    std::cin >> this->name;
}
/**
 * Costruttore
 * @param name Il nome dello User
 */
User::User(const std::string& name){
    this->name = name;
}

void User::mapChatToName(const std::string& chatName, std::shared_ptr<Chat> c){
    this->myChats.insert(std::make_pair(chatName, c));
    Notifier* n = new Notifier(this->name, c);
    this->myNotifiers.insert(std::make_pair(chatName, n));
    c->subscribe(n);
}

void User::unmapChatToName(const std::string& chatName){
    if(this->myChats.find(chatName) == this->myChats.end()) {
        throw std::runtime_error(this->name + " non fa parte del gruppo " + chatName);
    }
    Notifier* n = myNotifiers.find(chatName)->second;
    this->myChats.find(chatName)->second->unsubscribe(n);
    this->myChats.erase(chatName);
}

void User::createChat(User* u) {
    if(this->myChats.find(u->name) != this->myChats.end()){
        throw std::runtime_error("Esiste gia' una chat con " + u->name);
    }
    auto c = std::make_shared<Chat>();
    this->mapChatToName(u->name, c);
    u->mapChatToName(this->name, c);
}

void User::createGroupChat(const std::vector<User*>& users, const std::string& groupName){ //TODO mettere try/catch nel main
    if(this->myChats.find(groupName) != this->myChats.end()){
        throw std::runtime_error("Hai gia' un gruppo chiamato " + groupName);
    }
    auto gc = std::make_shared<GroupChat>(groupName);
    this->mapChatToName(groupName, gc);
    for (auto u: users) {
        u->mapChatToName(groupName, gc);
    }
}

void User::addUserToGroupChat( User *u, const std::string& groupName) {
    auto groupNameMapped = this->myChats.find(groupName);
    groupNameMapped != this->myChats.end() ? u->mapChatToName(groupName, groupNameMapped->second) : throw std::runtime_error("Non è stata trovata nessuna chat di gruppo " + groupName);
}
/**
 * Permette ad uno User di rimuovere un altro User da un gruppo a cui partecipa
 * @param groupName nome del gruppo da cui si vuole rimuovere lo User u
 * @param u User da rimuovere
 * @throws std::runtime_error se lo User che invoca il metodo non fa parte di nessun gruppo chiamato groupName
 */
void User::kickUserFromGroupChat(User* u, const std::string& groupName){
    auto groupNameMapped = this->myChats.find(groupName);
    groupNameMapped != this->myChats.end() ? u->unmapChatToName(groupName) : throw std::runtime_error("Non e' stata trovata nessuna chat di gruppo " + groupName);
}

void User::sendMessage(std::string txt, const std::string& _name) { //TODO mettere try/catch nel main
    if(myChats.find(_name) == myChats.end()){
        throw std::runtime_error("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message msg(this->name, _name, std::move(txt));
    c->addMessage(msg);
    sleep(1); //TODO inutile, serve a fare avere ai messaggi degli orari diversi
}

/**
 * Invoca il metodo readChat della chat mappata da chatName
 * @param chatName
 * @throws std::runtime_error Se non esiste nessuna chat che risponde al nome indicato in chatName
 */
void User::readChat(const std::string& chatName) const{
    std::cout << "Chat: " + chatName << std::endl;
    try {
        auto chatNameMapped = this->myChats.find(chatName);
        chatNameMapped != this->myChats.end() ? chatNameMapped->second->readChatMessages(this->name) : throw std::runtime_error("Non esiste nessuna chat " + chatName);
    } catch (std::out_of_range &o){
        std::cerr << "Out of range error: " << o.what() << std::endl;
    }
    std::cout << std::endl;
}

void User::readLastMessageFrom(const std::string& chatName) const{
    std::cout << "Ultimo messaggio dalla chat: " + chatName << std::endl;
    try {
        auto chatNameMapped = this->myChats.find(chatName);
        chatNameMapped != this->myChats.end() ? chatNameMapped->second->readLastMessage(this->name) : throw std::runtime_error("Non esiste nessuna chat " + chatName);
    } catch (std::out_of_range &o){
        std::cerr << "Out of range error: " << o.what() << std::endl;
    }
    std::cout << std::endl;
}

void User::leaveGroup(const std::string& groupName) {
    try {
        this->unmapChatToName(groupName);
        std::cout << "Hai lasciato il gruppo " + groupName << std::endl;
    } catch (std::runtime_error &r){
        std::cerr << r.what() << std::endl;
    }
}

void User::chatRegister() const {
    std::cout << " --- Registro delle Chat di " + name + " --- " << std::endl;
    for(auto receiver: myChats){
        if(std::shared_ptr<GroupChat> tmp = std::dynamic_pointer_cast<GroupChat>(receiver.second)){
            std::cout << "Gruppo " + receiver.first + ":\n";
            receiver.second->readChatMessages(this->name);
        } else {
            std::cout << receiver.first +"\n";
            receiver.second->readChatMessages(this->name);
        }
    }
}

/**
 * Indica il numero di messaggi non letti per una specifica chat
 * @param chat La chat di cui si vuole sapere il numero di messaggi non letti
 */
void User::getUnreadMessages(std::string chat) const{
    std::cout << this->name << ", hai "<< this->myNotifiers.find(chat)->second->getUnreadNotifications() << " messaggi non letti da " << chat << "." << std::endl;
}

/**
 * Indica il numero di messaggi non letti per ogni chat
 */
void User::getUnreadMessages() const {
    std::cout << this->name << ", non hai letto i seguenti messaggi:" << std::endl;
    for(auto chat = myChats.begin(); chat != myChats.end(); ++chat){
        std::cout << chat->first << ": " << this->myNotifiers.find(chat->first)->second->getUnreadNotifications() << std::endl;
    }
}

/**
 * Chiama showUnreadMessages su una specifica chat
 * @param chat
 */
void User::readUnreadMessages(std::string chat) {
    this->myChats.find(chat)->second->showUnreadMessages(this->name);
}

const std::map<std::string, Notifier *> &User::getMyNotifiers() const {
    return myNotifiers;
}

const std::map<std::string, std::shared_ptr<Chat>> &User::getMyChats() const {
    return myChats;
}
