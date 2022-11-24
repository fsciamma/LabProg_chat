//
// Created by filip on 23/11/2022.
//

#include <gtest/gtest.h>
#include "../Message.h"

TEST(Message, GetterSetter) {
    Message msg("Tester", "Questo è un messaggio di prova");

    ASSERT_EQ(msg.getSender(), "Tester");
    ASSERT_EQ(msg.getText(), "Questo è un messaggio di prova");
}

