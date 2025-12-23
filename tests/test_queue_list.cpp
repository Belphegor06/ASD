#include <gtest/gtest.h>
#include "../lib_queue_list/queue_list.h"

TEST(TestQueueList, is_empty_initially) {
    QueueList<int> q;
    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueueList, push_one_element) {
    QueueList<int> q;
    q.push(10);
    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 10);
}

TEST(TestQueueList, push_multiple_elements) {
    QueueList<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 30);
}

TEST(TestQueueList, pop_removes_front) {
    QueueList<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    q.pop();
    EXPECT_EQ(q.front(), 20);
}

TEST(TestQueueList, fifo_order) {
    QueueList<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);

    q.pop(); // 10
    q.pop(); // 20
    EXPECT_EQ(q.front(), 30);
}

TEST(TestQueueList, clear_queue) {
    QueueList<int> q;
    q.push(10);
    q.push(20);
    q.clear();
    EXPECT_TRUE(q.is_empty());
}

TEST(TestQueueList, pop_from_empty_throws) {
    QueueList<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(TestQueueList, front_from_empty_throws) {
    QueueList<int> q;
    EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(TestQueueList, back_from_empty_throws) {
    QueueList<int> q;
    EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(TestQueueList, many_elements_fifo) {
    QueueList<int> q;
    for (int i = 1; i <= 100; i++)
        q.push(i);

    for (int i = 1; i <= 90; i++)
        q.pop();

    EXPECT_EQ(q.front(), 91);
    EXPECT_EQ(q.back(), 100);
}
