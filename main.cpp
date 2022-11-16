#include <iostream>
#include "Chat.h"
#include "User.h"

int main() {
    User* u1 = new User();
    User* u2 = new User();
    User* u3 = new User();

    u1->createChat(u2);
    u1->createChat(u3);
    u1->sendMessage();
}
