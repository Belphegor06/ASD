#include <gtest/gtest.h>

#include "../lib_unsorted_table_on_list/unsorted_table_on_list.h"


TEST(TestUnsortedTableOnList, can_create_table)
{
    UnsortedTableOnList<int, int> table;

    ASSERT_EQ(0, table.size());
    ASSERT_TRUE(table.empty());
}


TEST(TestUnsortedTableOnList, can_insert_element)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_EQ(1, table.size());
    ASSERT_EQ(10, table.find(1));
}


TEST(TestUnsortedTableOnList, throw_when_insert_duplicate_key)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_THROW(table.insert(1, 20), std::logic_error);
}


TEST(TestUnsortedTableOnList, can_find_element)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);

    ASSERT_EQ(10, table.find(1));
    ASSERT_EQ(20, table.find(2));
}


TEST(TestUnsortedTableOnList, throw_when_find_non_existing_key)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_THROW(table.find(2), std::logic_error);
}


TEST(TestUnsortedTableOnList, can_erase_element)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);

    table.erase(1);

    ASSERT_EQ(1, table.size());
    ASSERT_FALSE(table.contains(1));
    ASSERT_TRUE(table.contains(2));
}


TEST(TestUnsortedTableOnList, throw_when_erase_non_existing_key)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_THROW(table.erase(2), std::logic_error);
}


TEST(TestUnsortedTableOnList, contains_returns_true)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_TRUE(table.contains(1));
}


TEST(TestUnsortedTableOnList, contains_returns_false)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_FALSE(table.contains(2));
}


TEST(TestUnsortedTableOnList, can_clear_table)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);
    table.insert(2, 20);

    table.clear();

    ASSERT_TRUE(table.empty());
    ASSERT_EQ(0, table.size());
}


TEST(TestUnsortedTableOnList, can_insert_after_clear)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    table.clear();

    table.insert(2, 20);

    ASSERT_EQ(1, table.size());
    ASSERT_EQ(20, table.find(2));
}


TEST(TestUnsortedTableOnList, size_changes_correctly)
{
    UnsortedTableOnList<int, int> table;

    ASSERT_EQ(0, table.size());

    table.insert(1, 10);
    ASSERT_EQ(1, table.size());

    table.insert(2, 20);
    ASSERT_EQ(2, table.size());

    table.erase(1);
    ASSERT_EQ(1, table.size());
}


TEST(TestUnsortedTableOnList, table_is_not_empty_after_insert)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    ASSERT_FALSE(table.empty());
}


TEST(TestUnsortedTableOnList, can_change_value_through_find)
{
    UnsortedTableOnList<int, int> table;

    table.insert(1, 10);

    table.find(1) = 100;

    ASSERT_EQ(100, table.find(1));
}


TEST(TestUnsortedTableOnList, can_work_with_many_elements)
{
    UnsortedTableOnList<int, int> table;

    for (int i = 0; i < 100; i++)
    {
        table.insert(i, i * 10);
    }

    ASSERT_EQ(100, table.size());

    for (int i = 0; i < 100; i++)
    {
        ASSERT_EQ(i * 10, table.find(i));
    }
}