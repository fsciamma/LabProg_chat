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
    this->myNotifier = new Notifier(this->name);
    this->BN = new badNotifier(4);
}
/**
 * Costruttore
 * @param name Il nome dello User
 */
User::User(const std::string& name){
    this->name = name;
    this->myNotifier = new Notifier(name);
    this->BN = new badNotifier(4);
}

void User::mapChatToName(const std::string& chatName, std::shared_ptr<Chat> c){
    this->myChats.insert(std::make_pair(chatName, c));
    c->subscribe(this->myNotifier);
}

void User::unmapChatToName(const std::string& chatName){
    if(this->myChats.find(chatName) == this->myChats.end()) {
        throw std::runtime_error(this->name + " non fa parte del gruppo " + chatName);
    }
    this->myChats.find(chatName)->second->unsubscribe(this->myNotifier);
    this->myChats.erase(chatName);
}

void User::createChat(User* u) {
    if(this->myChats.find(u->name) != this->myChats.end()){ //TODO mettere try/catch nel main
        throw std::runtime_error("Esiste già una chat con " + u->name);
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
    gc->subscribe(this->BN); //Usato solo per avere una seconda sottoclasse di Observer, per mettere in risalto il controllo tramite dynamic_cast
    for (auto u: users) {
        u->mapChatToName(groupName, gc);
    }
}

//TODO creare metodi per aggiungere o togliere utenti ad una chat di gruppo
void User::addUserToGroupChat(const std::string& groupName, User *u) {
    auto groupNameMapped = this->myChats.find(groupName);
    groupNameMapped != this->myChats.end() ? u->mapChatToName(groupName, groupNameMapped->second) : throw std::runtime_error("Non è stata trovata nessuna chat di gruppo " + groupName);
}
/**
 * Permette ad uno User di rimuovere un altro User da un gruppo a cui partecipa
 * @param groupName nome del gruppo da cui si vuole rimuovere lo User u
 * @param u User da rimuovere
 * @throws std::runtime_error se lo User che invoca il metodo non fa parte di nessun gruppo chiamato groupName
 */
void User::kickUserFromGroupChat(const std::string& groupName, User* u){
    auto groupNameMapped = this->myChats.find(groupName);
    groupNameMapped != this->myChats.end() ? u->unmapChatToName(groupName) : throw std::runtime_error("Non e' stata trovata nessuna chat di gruppo " + groupName);
}

void User::sendMessage(std::string txt, const std::string& _name) { //TODO mettere try/catch nel main
    if(myChats.find(_name) == myChats.end()){
        throw std::runtime_error("Non e' stata trovata nessuna chat con " + _name);
    }
    auto c = myChats.find(_name)->second;
    Message* msg = new Message(this->name, std::move(txt));
    c->addMessage(*msg);
    sleep(1);
}

/**
 *
 * @param chatName
 * @throws std::runtime_error Se non esiste nessuna chat che risponde al nome indicato in chatName
 */
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

void User::leaveGroup(const std::string& groupName) { //TODO modificare per perfezionare , integrarlo con kickUser
    try {
        this->unmapChatToName(groupName);
        std::cout << "Hai lasciato il gruppo " + groupName << std::endl;
    } catch (std::runtime_error &r){
        std::cerr << r.what() << std::endl;
    }
}
