#include <gtest/gtest.h>
#include "../lib_wlist/wlist.h"
#include <stdexcept>

TEST(WListBasic, empty_list) {
    WList<int> list;
    EXPECT_TRUE(list.is_empty());
}

TEST(WListPush, push_front) {
    WList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    ASSERT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front()); // 3
    ASSERT_NO_THROW(list.pop_front()); // 2
    ASSERT_NO_THROW(list.pop_front()); // 1

    EXPECT_TRUE(list.is_empty());
}

TEST(WListPush, push_back) {
    WList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 2
    ASSERT_NO_THROW(list.pop_front()); // 3

    EXPECT_TRUE(list.is_empty());
}

TEST(WListConstructor, copy_constructor) {
    WList<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    WList<int> copy(original);

    ASSERT_NO_THROW(original.pop_front()); // меняем оригинал
    EXPECT_FALSE(copy.is_empty());         // копия остаётся непустой
}

TEST(WListPop, pop_front) {
    WList<int> list;
    list.push_back(1);
    list.push_back(2);

    ASSERT_NO_THROW(list.pop_front());
    EXPECT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front());
    EXPECT_TRUE(list.is_empty());
}

TEST(WListPop, pop_back) {
    WList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_NO_THROW(list.pop_back()); // удаляем 3

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 2

    EXPECT_TRUE(list.is_empty());
}

TEST(WListPop, pop_empty_list) {
    WList<int> list;
    EXPECT_THROW(list.pop_front(), std::runtime_error);
    EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(WListErase, erase_node) {
    WList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // безопасно находим второй узел
    Node<int>* cur = list.head()->next;
    ASSERT_NO_THROW(list.erase(cur)); // удаляем 2

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 3

    EXPECT_TRUE(list.is_empty());
}

TEST(WListErase, erase_head_tail) {
    WList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_NO_THROW(list.erase(list.head())); // удаляем 1
    ASSERT_NO_THROW(list.erase(list.tail())); // удаляем 3

    ASSERT_NO_THROW(list.pop_front()); // 2
    EXPECT_TRUE(list.is_empty());
}

TEST(WListErase, erase_invalid_node) {
    WList<int> list;
    EXPECT_THROW(list.erase(nullptr), std::invalid_argument);
}

TEST(WListSequence, insert_before_head_and_after_tail) {
    WList<int> list;
    list.push_back(2); // 2

    ASSERT_NO_THROW(list.insert_before(list.head(), 1)); // 1 2
    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 2);

    ASSERT_NO_THROW(list.insert_after(list.tail(), 3)); // 1 2 3
    EXPECT_EQ(list.head()->value, 1);
    EXPECT_EQ(list.tail()->value, 3);

    Node<int>* cur = list.head();
    int expected[] = { 1, 2, 3 };
    int idx = 0;
    while (cur != nullptr) {
        EXPECT_EQ(cur->value, expected[idx++]);
        cur = cur->next;
    }
}

TEST(WListSequence, erase_all_nodes) {
    WList<int> list;
    for (int i = 1; i <= 5; ++i)
        list.push_back(i); // 1 2 3 4 5

    while (!list.is_empty()) {
        // всегда берём голову заново
        list.erase(list.head());
    }

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.tail(), nullptr);
}

TEST(WListSequence, insert_and_erase_multiple_safe) {
    WList<int> list;
    list.push_back(1);
    list.push_back(3);

    // вставка после головы
    Node<int>* first = list.head();
    list.insert_after(first, 2);  // 1 2 3

    // вставка перед хвостом
    Node<int>* last = list.tail();
    list.insert_before(last, 4);  // 1 2 4 3

    Node<int>* cur = list.head();
    int expected[] = { 1, 2, 4, 3 };
    int idx = 0;
    while (cur != nullptr) {
        EXPECT_EQ(cur->value, expected[idx++]);
        cur = cur->next;
    }

    // безопасное удаление узла со значением 2
    cur = list.head();
    while (cur != nullptr && cur->value != 2) cur = cur->next;
    ASSERT_NE(cur, nullptr);
    list.erase(cur); // 1 4 3

    // проверка после удаления
    cur = list.head();
    int expected2[] = { 1, 4, 3 };
    idx = 0;
    while (cur != nullptr) {
        EXPECT_EQ(cur->value, expected2[idx++]);
        cur = cur->next;
    }

    // удаляем все узлы через голову
    while (!list.is_empty()) {
        list.erase(list.head());
    }

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.head(), nullptr);
    EXPECT_EQ(list.tail(), nullptr);
}
