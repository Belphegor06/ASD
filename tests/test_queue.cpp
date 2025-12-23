#include <gtest/gtest.h>
#include "../lib_queue/queue.h"

TEST(TestTQueue, is_empty_initially) {
    TQueue<int> q(5);
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(TestTQueue, push_one_element) {
    TQueue<int> q(5);
    q.push(10);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 10);
    EXPECT_EQ(q.size(), 1);
}

TEST(TestTQueue, push_multiple_elements) {
    TQueue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 30);
    EXPECT_EQ(q.size(), 3);
}

TEST(TestTQueue, pop_removes_front) {
    TQueue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);

    q.pop();
    EXPECT_EQ(q.front(), 20);
    EXPECT_EQ(q.size(), 2);
}

TEST(TestTQueue, cyclic_behavior) {
    TQueue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    EXPECT_EQ(q.size(), 5);

    q.pop(); // front -> 20
    q.push(60); // wrap-around
    EXPECT_EQ(q.back(), 60);
    EXPECT_EQ(q.front(), 20);
}

TEST(TestTQueue, fifo_order) {
    TQueue<int> q(5);
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    q.pop(); // 10
    q.pop(); // 20
    EXPECT_EQ(q.front(), 30);
}

TEST(TestTQueue, clear_queue) {
    TQueue<int> q(5);
    q.push(10);
    q.push(20);
    q.clear();
    EXPECT_TRUE(q.is_empty());
}

TEST(TestTQueue, pop_from_empty_throws) {
    TQueue<int> q(5);
    EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(TestTQueue, front_from_empty_throws) {
    TQueue<int> q(5);
    EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(TestTQueue, large_number_of_elements) {
    TQueue<int> q(200); // увеличенный буфер
    for (int i = 1; i <= 100; i++) q.push(i);
    EXPECT_EQ(q.size(), 100);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 100);
}

TEST(TestTQueue, after_multiple_pops) {
    TQueue<int> q(200);
    for (int i = 1; i <= 100; i++) q.push(i);
    for (int i = 1; i <= 90; i++) q.pop();
    EXPECT_EQ(q.size(), 10);
    EXPECT_EQ(q.front(), 91);
}
