//
// Created by filip on 23/11/2022.
//

#include <gtest/gtest.h>
#include "../Chat.h"


TEST(Chat, readMessages){
    Chat* c = new Chat();

    ASSERT_THROW(c->readChatMessages(), std::out_of_range);
    ASSERT_THROW(c->readLastMessage(), std::out_of_range);
}
