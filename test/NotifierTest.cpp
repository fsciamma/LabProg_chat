//
// Created by filip on 05/12/2022.
//

#include <gtest/gtest.h>
#include "../Notifier.h"
#include "../User.h"

TEST(Notifier, getNotifications){
    User u1("Tester");
    User u2("SecondTester");
    u1.createChat(&u2);
    Notifier* n = u1.getMyNotifiers().find("SecondTester")->second;
    ASSERT_EQ(n->getUnreadNotifications(), 0);
    u2.sendMessage("Messaggio 1", "Tester");
    ASSERT_EQ(n->getUnreadNotifications(), 1);
    u1.readUnreadMessages("SecondTester");
    ASSERT_EQ(n->getUnreadNotifications(), 0);
}