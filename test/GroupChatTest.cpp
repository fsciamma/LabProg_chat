//
// Created by filip on 24/11/2022.
//

#include <gtest/gtest.h>
#include "../GroupChat.h"

TEST(GroupChat, Getter){
    GroupChat* gc = new GroupChat("Group");
    ASSERT_EQ(gc->getGroupName(), "Group");
}


TEST(GroupChat, readMessages){
    GroupChat* gc = new GroupChat("Group");
    ASSERT_THROW(gc->readChatMessages(), std::out_of_range);
    ASSERT_THROW(gc->readLastMessage(), std::out_of_range);
}