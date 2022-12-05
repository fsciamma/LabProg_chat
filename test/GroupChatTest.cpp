//
// Created by filip on 24/11/2022.
//

#include <gtest/gtest.h>
#include "../GroupChat.h"
#include "../User.h"

TEST(GroupChat, Getter){
    User u1("Tester");
    User u2("SecondTester");
    User u3("ThirdTester");
    std::vector<User*> vTest;
    vTest.push_back(&u2);
    vTest.push_back(&u3);
    u1.createGroupChat(vTest, "Gruppo");
    std::shared_ptr<Chat> gc = u1.getMyChats().find("Gruppo")->second;

    ASSERT_EQ(std::dynamic_pointer_cast<GroupChat>(gc)->getGroupName(), "Gruppo");
}


TEST(GroupChat, readMessages){
    User u1("Tester");
    User u2("SecondTester");
    User u3("ThirdTester");
    std::vector<User*> vTest;
    vTest.push_back(&u2);
    vTest.push_back(&u3);
    u1.createGroupChat(vTest, "Gruppo");
    std::shared_ptr<Chat> gc = u1.getMyChats().find("Gruppo")->second;
    ASSERT_THROW(std::dynamic_pointer_cast<GroupChat>(gc)->readChatMessages("Tester"), std::out_of_range);
    ASSERT_THROW(std::dynamic_pointer_cast<GroupChat>(gc)->readLastMessage("SecondTester"), std::out_of_range);

}