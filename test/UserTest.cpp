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

    User* u3 = new User("ThirdTester");

}