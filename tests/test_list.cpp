#include <gtest/gtest.h>
#include "../lib_list/list.h"
#include <stdexcept>


TEST(ListBasic, empty_list) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
}


TEST(ListPush, push_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    ASSERT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front()); // 3
    ASSERT_NO_THROW(list.pop_front()); // 2
    ASSERT_NO_THROW(list.pop_front()); // 1

    EXPECT_TRUE(list.is_empty());
}

TEST(ListPush, push_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 2
    ASSERT_NO_THROW(list.pop_front()); // 3

    EXPECT_TRUE(list.is_empty());
}


TEST(ListConstructor, copy_constructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    // меняем оригинал
    ASSERT_NO_THROW(original.pop_front());

    // копия должна остаться непустой
    EXPECT_FALSE(copy.is_empty());
}


TEST(ListInsert, insert_by_position) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    ASSERT_NO_THROW(list.insert(1, 2)); // между 1 и 3

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 2
    ASSERT_NO_THROW(list.pop_front()); // 3

    EXPECT_TRUE(list.is_empty());
}

TEST(ListInsert, insert_invalid_position) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW({
        list.insert(5, 2);
        }, std::out_of_range);
}


TEST(ListPop, pop_front) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    ASSERT_NO_THROW(list.pop_front());
    EXPECT_FALSE(list.is_empty());

    ASSERT_NO_THROW(list.pop_front());
    EXPECT_TRUE(list.is_empty());
}

TEST(ListPop, pop_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_NO_THROW(list.pop_back());

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 2

    EXPECT_TRUE(list.is_empty());
}

TEST(ListPop, pop_empty_list) {
    List<int> list;

    EXPECT_THROW({
        list.pop_front();
        }, std::runtime_error);
}


TEST(ListErase, erase_by_position) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_NO_THROW(list.erase(1)); // удаляем 2

    ASSERT_NO_THROW(list.pop_front()); // 1
    ASSERT_NO_THROW(list.pop_front()); // 3

    EXPECT_TRUE(list.is_empty());
}

TEST(ListErase, erase_invalid_position) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW({
        list.erase(5);
        }, std::out_of_range);
}
