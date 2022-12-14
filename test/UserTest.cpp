//
// Created by filip on 24/11/2022.
//

#include <gtest/gtest.h>
#include "../User.h"

TEST(User, chatMethods){
    User u1("Tester");
    User u2("OtherTester");

    ASSERT_THROW(u1.sendMessage("Messaggio di test", "OtherTester"), std::runtime_error);
    ASSERT_NO_THROW(u1.createChat(&u2));
    ASSERT_THROW(u2.createChat(&u1), std::runtime_error);

    ASSERT_NO_THROW(u1.sendMessage("Messaggio di test", "OtherTester"));
    ASSERT_NO_THROW(u2.readChat("Tester"));
    ASSERT_NO_THROW(u2.readLastMessageFrom("Tester"));

}

TEST(User, groupMethods){
    User u1("Tester");
    User u2("SecondTester");
    User u3("ThirdTester");

    std::vector<User*> testers;
    testers.push_back(&u2);
    testers.push_back(&u3);
    ASSERT_NO_THROW(u1.createGroupChat(testers, "GroupTest"));
    ASSERT_THROW(u1.createGroupChat(testers, "GroupTest"), std::runtime_error);

    User u4("FourthTester");

    std::cout << "u1 e u3 ricevono il messaggio di u2; u4 non fa parte del gruppo." << std::endl;
    ASSERT_NO_THROW(u2.sendMessage("Messaggio di test - 1", "GroupTest"));
    ASSERT_THROW(u4.sendMessage("Messaggio di test - 2", "GroupTest"), std::runtime_error);
    ASSERT_THROW(u4.readChat("GroupTest"), std::runtime_error);
    std::cout << std::endl;

    u1.addUserToGroupChat(&u4, "GroupTest");
    std::cout << "u2, u3 e u4 ricevono il messaggio di u1." << std::endl;
    ASSERT_NO_THROW(u1.sendMessage("Messaggio di test - 3", "GroupTest"));
    u1.kickUserFromGroupChat(&u2, "GroupTest");
    u1.leaveGroup("GroupTest");
    std::cout << std::endl;

    std::cout << "Solo u4 riceve il messaggio di u3; u1 e u2 non fanno più parte del gruppo." << std::endl;
    ASSERT_NO_THROW(u3.sendMessage("Messaggio di test - 4", "GroupTest"));
    ASSERT_THROW(u2.sendMessage("Messaggio di test - 5", "GroupTest"), std::runtime_error);
    ASSERT_NO_THROW(u4.readLastMessageFrom("GroupTest"));
}