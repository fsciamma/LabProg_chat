//
// Created by filip on 24/11/2022.
//

#include <gtest/gtest.h>
#include "../User.h"

TEST(User, chatMethods){
    User* u1 = new User("Tester");
    User* u2 = new User("OtherTester");

    ASSERT_NO_THROW(u1->createChat(u2));
    ASSERT_THROW(u2->createChat(u1), std::runtime_error);
}

TEST(User, groupMethods){
    User* u1 = new User("Tester");
    User* u2 = new User("SecondTester");
    User* u3 = new User("ThirdTester");

    std::vector<User*> testers;
    testers.push_back(u2);
    testers.push_back(u3);
    ASSERT_NO_THROW(u1->createGroupChat(testers, "GroupTest"));
    ASSERT_THROW(u1->createGroupChat(testers, "GroupTest"), std::runtime_error);

    User* u4 = new User("FourthTester");

    std::cout << "u1 e u3 ricevono il messaggio di u2; u4 non fa parte del gruppo." << std::endl;
    ASSERT_NO_THROW(u2->sendMessage("Messaggio di test", "GroupTest"));
    ASSERT_THROW(u4->sendMessage("Messaggio di test", "GroupTest"), std::runtime_error);
    std::cout << std::endl;

    u1->addUserToGroupChat("GroupTest", u4);
    std::cout << "u2, u3 e u4 ricevono il messaggio di u1." << std::endl;
    ASSERT_NO_THROW(u1->sendMessage("Messaggio di test", "GroupTest"));
    u1->kickUserFromGroupChat("GroupTest", u2);
    u1->leaveGroup("GroupTest");
    std::cout << std::endl;

    std::cout << "Solo u4 riceve il messaggio di u3; u1 e u2 non fanno più parte del gruppo." << std::endl;
    ASSERT_NO_THROW(u3->sendMessage("Messaggio di test", "GroupTest"));
    ASSERT_THROW(u2->sendMessage("Messaggio di test", "GroupTest"), std::runtime_error);
}