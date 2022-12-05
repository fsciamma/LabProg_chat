//
// Created by filip on 15/11/2022.
//

#include "Chat.h"
#include "Notifier.h"

Chat::Chat() {
    std::cout << "E' stata creata una chat" << std::endl; //TODO levare
}

void Chat::subscribe(Observer *o) {
    readers.push_back(o);
}

void Chat::unsubscribe(Observer *o) {
    readers.remove(o);
}

void Chat::notifyObservers(Message msg) const {
    for(auto obs: readers){
        if(Notifier* obsNot = dynamic_cast<Notifier*>(obs)) {
            if (obsNot->getName() != msg.getSender()) {
                obs->update(msg);
            }
        }
    }
}

void Chat::addMessage(Message msg) {
    this->messages.push_back(msg);
    notifyObservers(msg);
}

/**
 * Stampa a schermo i messaggi presenti nella Chat
 * @param userName L'identificativo dello User che legge i messaggi. Viene passato al metodo setRead di ogni messaggio visualizzato con questa funzione
 */
void Chat::readChatMessages(const std::string &userName) {
    if(this->messages.empty()){
        throw std::out_of_range("Non ci sono ancora messaggi");
    }
    for(auto & msg : this->messages){
        msg.setRead(userName);
        char timestamp[40];
        time_t _t = msg.getMyTime();
        struct tm* localTime = localtime(&_t);
        strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
        std::cout << timestamp << " - " + msg.getSender() + " : " + msg.getText() << std::endl;
    }
}

/**
 * Stampa a schermo l'ultimo messaggio presente nella Chat
 * @param userName L'identificativo dello User che legge il messaggio. Viene passato al metodo setRead del messaggio visualizzato con questa funzione
 */
void Chat::readLastMessage(const std::string &userName) {
    if(this->messages.empty()){
        throw std::out_of_range("Non ci sono ancora messaggi");
    }
    auto & msg = this->messages.back();
    msg.setRead(userName);
    time_t _t = msg.getMyTime();
    struct tm* localTime = localtime(&_t);
    char timestamp[40];
    strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
    std::cout << timestamp << " " + msg.getSender() + ": " + msg.getText() << std::endl;
}

/**
 * Conta quanti messaggi della chat non sono stati letti dallo User
 * @param userName L'identificativo dello User che vuole sapere quanti messaggi non letti ci sono nella Chat. Viene passato al metodo isRead del messaggio visualizzato con questa funzione
 * @return il numero di messaggi non letti da userName
 */
int Chat::getUnreadMessages(const std::string &userName) const{
    int unread = 0;
    for(auto msg: this->messages){
        if(!msg.isRead(userName)){
            unread++;
        }
    }
    return unread;
}

/**
 * Stampa a schermo tutti i messaggi che ancora non sono stati letti dallo User che invoca il metodo
 * @param userName L'identificativo dello User che chiama il metodo.
 */
void Chat::showUnreadMessages(const std::string &userName) {
    if(this->messages.empty()){
        throw std::out_of_range("Non ci sono ancora messaggi");
    }
    for(auto & msg : this->messages){
        if(!msg.isRead(userName)){
            msg.setRead(userName);
            time_t _t = msg.getMyTime();
            struct tm* localTime = localtime(&_t);
            char timestamp[40];
            strftime(timestamp, 40, "[%d/%m, %H:%M:%S]", localTime);
            std::cout << timestamp << " " + msg.getSender() + ": " + msg.getText() << std::endl;
        }
    }
}
