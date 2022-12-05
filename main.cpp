#include <iostream>
#include "Chat.h"
#include "User.h"

int main() {
    User* filippo = new User("Filippo");
    User* francesco = new User("Francesco");

    User* vittorio = new User("Vittorio");
    User* matteo = new User("Matteo");

    User* giorgio = new User("Giorgio");
    User* leonardo = new User("Leonardo");
    User* tommaso = new User("Tommaso");

    //Chat singole
    try {
        filippo->createChat(francesco);
        filippo->sendMessage("Ciao", "Francesco");
        filippo->sendMessage("Come va?", "Francesco");
        francesco->getUnreadMessages("Filippo");
        filippo->getUnreadMessages("Francesco");
        francesco->sendMessage("Tutto bene, grazie");
        francesco->readChat("Filippo");
        francesco->getUnreadMessages("Filippo");
        filippo->getUnreadMessages("Francesco");
        filippo->readLastMessageFrom("Francesco");
        filippo->getUnreadMessages("Francesco");
        francesco->createChat(filippo);
    } catch (std::runtime_error &r){
        std::cerr << r.what() << std::endl;
    }

    std::vector<User*> studenti;
    studenti.push_back(vittorio);
    studenti.push_back(matteo);
    try {
        filippo->createGroupChat(studenti, "Uni");
        vittorio->sendMessage("Domani ci siete?", "Uni");
        matteo->sendMessage("Solo la mattina", "Uni");
        filippo->sendMessage("Presente", "Uni");
        matteo->readChat("Uni");
    } catch (std::runtime_error &r){
        std::cerr << r.what() << std::endl;
    }

    std::vector<User*> tifosi;
    tifosi.push_back(giorgio);
    tifosi.push_back(leonardo);
    try{
        filippo->createGroupChat(tifosi, "Stadio");
        giorgio->sendMessage("Chi viene domenica?", "Stadio");
        leonardo->addUserToGroupChat(tommaso, "Stadio");
        leonardo->sendMessage("Ho aggiunto anche tommi, almeno legge pure lui", "Stadio");
        tommaso->sendMessage("Ragazzi io non ci sono, tifo Milan", "Stadio");
        filippo->readChat("Stadio");
    } catch (std::runtime_error &r){
        std::cerr << r.what() << std::endl;
    }

    filippo->getUnreadMessages();
    filippo->getUnreadMessages("Uni");
    filippo->readUnreadMessages("Uni");
    filippo->getUnreadMessages();
    filippo->chatRegister();
    vittorio->chatRegister();
}
