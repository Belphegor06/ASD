#include <gtest/gtest.h>
#include "../lib_stack/stack.h"  

TEST(TestTStack, is_empty_initially) {
    TStack<int> s;
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(TestTStack, push_one_element) {
    TStack<int> s;
    s.push(10);
    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 10);
}

TEST(TestTStack, push_multiple_elements) {
    TStack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.top(), 30);
}

TEST(TestTStack, pop_removes_top) {
    TStack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    s.pop();
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.top(), 20);
}

TEST(TestTStack, pop_until_empty) {
    TStack<int> s;
    s.push(10);
    s.push(20);

    s.pop();
    s.pop();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestTStack, pop_from_empty_throws) {
    TStack<int> s;
    EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(TestTStack, reuse_after_clear) {
    TStack<int> s;
    s.push(5);
    s.push(15);
    s.clear();
    EXPECT_TRUE(s.is_empty());
}

TEST(TestTStack, top_from_empty_throws) {
    TStack<int> s;
    EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(TestTStack, push_and_top_many_elements) {
    TStack<int> s;
    for (int i = 0; i < 100; i++) s.push(i);

    EXPECT_EQ(s.size(), 100);
    EXPECT_EQ(s.top(), 99);
}

TEST(TestTStack, pop_lifo_order) {
    TStack<int> s;
    for (int i = 0; i < 100; i++) s.push(i);

    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.is_empty());
}

TEST(TestTStack, const_top) {
    const TStack<int> cs = [] {
        TStack<int> tmp;
        tmp.push(7);
        tmp.push(8);
        return tmp;
        }();
    EXPECT_EQ(cs.top(), 8);
}
