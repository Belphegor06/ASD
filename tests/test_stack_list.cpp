#include <gtest/gtest.h>
#include "../lib_stack_list/stack_list.h"

TEST(TestStackList, is_empty_initially) {
    StackList<int> s;
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStackList, push_one_element) {
    StackList<int> s;
    s.push(10);
    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.top(), 10);
}

TEST(TestStackList, push_multiple_elements) {
    StackList<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    EXPECT_EQ(s.top(), 30);
}

TEST(TestStackList, pop_removes_top) {
    StackList<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    s.pop();
    EXPECT_EQ(s.top(), 20);
}

TEST(TestStackList, pop_until_empty) {
    StackList<int> s;
    s.push(10);
    s.push(20);

    s.pop();
    s.pop();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStackList, pop_from_empty_throws) {
    StackList<int> s;
    EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(TestStackList, reuse_after_clear) {
    StackList<int> s;
    s.push(5);
    s.push(15);
    s.clear();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStackList, top_from_empty_throws) {
    StackList<int> s;
    EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(TestStackList, push_and_top_many_elements) {
    StackList<int> s;
    for (int i = 0; i < 100; i++)
        s.push(i);

    EXPECT_EQ(s.top(), 99);
}

TEST(TestStackList, pop_lifo_order) {
    StackList<int> s;
    for (int i = 0; i < 100; i++)
        s.push(i);

    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.is_empty());
}

TEST(TestStackList, const_top) {
    const StackList<int> cs = [] {
        StackList<int> tmp;
        tmp.push(7);
        tmp.push(8);
        return tmp;
        }();

    EXPECT_EQ(cs.top(), 8);
}
