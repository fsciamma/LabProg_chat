//
// Created by filip on 23/11/2022.
//

#include <gtest/gtest.h>
#include "../Chat.h"
#include "../User.h"


TEST(Chat, readMessages){
    User u1("Tester");
    User u2("SecondTester");
    u1.createChat(&u2);
    std::shared_ptr<Chat> c = u1.getMyChats().find("SecondTester")->second;

    ASSERT_THROW(c->readChatMessages("SecondTester"), std::out_of_range);
    ASSERT_THROW(c->readLastMessage("SecondTester"), std::out_of_range);

    u2.sendMessage("Messaggio 1", "Tester");

    ASSERT_NO_THROW(c->readChatMessages("SecondTester"));
    ASSERT_NO_THROW(c->readLastMessage("SecondTester"));
}
