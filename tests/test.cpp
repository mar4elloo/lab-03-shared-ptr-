// Copyright 2020 Your Name <a.mark.2001@mail.ru>

#include <gtest/gtest.h>
#include <header.hpp>
#include <string>

TEST(shared_ptr, check_empty1) {
    EXPECT_TRUE(true);
}

TEST(shared_ptr, check_empty2) {
    SharedPtr<std::string> null{};
    EXPECT_FALSE(null);
}

TEST(shared_ptr, check_reset) {
    SharedPtr<int> ptr_1(new int(0));
    EXPECT_EQ(*ptr_1, 0);
    ptr_1.reset();
    EXPECT_FALSE(ptr_1);
    ptr_1.reset(new int(1));
    EXPECT_EQ(*ptr_1, 1);
    EXPECT_EQ(ptr_1.use_count(), 1);
}

TEST(shared_ptr, check_swap) {
    SharedPtr<int> ptr_1(new int(0));
    SharedPtr<int> ptr_2(new int(1));
    EXPECT_EQ(*ptr_1, 0);
    ptr_1.swap(ptr_2);
    EXPECT_EQ(*ptr_1, 1);
    EXPECT_EQ(ptr_1.use_count(), 1);
    EXPECT_EQ(*ptr_2, 0);
    EXPECT_EQ(ptr_1.use_count(), 1);
}

TEST(shared_ptr, check_move) {
    SharedPtr<int> ptr_1(new int(0));
    SharedPtr<int> ptr_2 =
            SharedPtr<int>{new int(1)};
    EXPECT_EQ(*ptr_1, 0);
    EXPECT_EQ(ptr_1.use_count(), 1);
    ptr_1 = std::move(ptr_2);
    EXPECT_EQ(*ptr_1, 1);
    EXPECT_EQ(ptr_1.use_count(), 1);
}

TEST(shared_ptr, check_copy) {
    SharedPtr<int> ptr_1{new int(0)};
    EXPECT_EQ(*ptr_1, 0);
    EXPECT_EQ(ptr_1.use_count(), 1);
    auto ptr_2 = ptr_1;
    EXPECT_TRUE(ptr_2);
    EXPECT_TRUE(ptr_1);
    EXPECT_EQ(*ptr_2, 0);
    EXPECT_EQ(ptr_1.use_count(), 2);
    auto ptr_3(ptr_2);
    EXPECT_TRUE(ptr_3);
    EXPECT_EQ(*ptr_3, 0);
    EXPECT_EQ(ptr_3.use_count(), 3);
    EXPECT_EQ(ptr_1.get(), ptr_3.get());
}
