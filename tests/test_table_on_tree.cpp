#include <gtest/gtest.h>

#include "../lib_table_on_tree/table_on_tree.h"

TEST(TestTableOnTree, default_constructor_creates_empty_table)
{
    TableOnTree<int, std::string> table;

    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(TestTableOnTree, insert_one_element)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");

    EXPECT_FALSE(table.empty());
    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.contains(1));
}

TEST(TestTableOnTree, insert_several_elements)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.size(), 3);

    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(2));
    EXPECT_TRUE(table.contains(3));
}

TEST(TestTableOnTree, insert_duplicate_key_throws_exception)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");

    EXPECT_THROW(table.insert(1, "another"), std::runtime_error);
}

TEST(TestTableOnTree, find_existing_key_returns_value)
{
    TableOnTree<int, std::string> table;

    table.insert(10, "ten");

    EXPECT_EQ(table.find(10), "ten");
}

TEST(TestTableOnTree, find_non_existing_key_throws_exception)
{
    TableOnTree<int, std::string> table;

    table.insert(10, "ten");

    EXPECT_THROW(table.find(100), std::runtime_error);
}

TEST(TestTableOnTree, contains_returns_true_for_existing_key)
{
    TableOnTree<int, std::string> table;

    table.insert(5, "five");

    EXPECT_TRUE(table.contains(5));
}

TEST(TestTableOnTree, contains_returns_false_for_missing_key)
{
    TableOnTree<int, std::string> table;

    table.insert(5, "five");

    EXPECT_FALSE(table.contains(100));
}

TEST(TestTableOnTree, erase_existing_key)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);

    EXPECT_FALSE(table.contains(2));
    EXPECT_EQ(table.size(), 2);

    EXPECT_TRUE(table.contains(1));
    EXPECT_TRUE(table.contains(3));
}

TEST(TestTableOnTree, erase_root_element)
{
    TableOnTree<int, std::string> table;

    table.insert(10, "ten");
    table.insert(20, "twenty");
    table.insert(30, "thirty");

    table.erase(10);

    EXPECT_FALSE(table.contains(10));
    EXPECT_EQ(table.size(), 2);

    EXPECT_TRUE(table.contains(20));
    EXPECT_TRUE(table.contains(30));
}

TEST(TestTableOnTree, erase_last_element)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");

    table.erase(1);

    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(TestTableOnTree, erase_non_existing_key_throws_exception)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");

    EXPECT_THROW(table.erase(100), std::runtime_error);
}

TEST(TestTableOnTree, erase_from_empty_table_throws_exception)
{
    TableOnTree<int, std::string> table;

    EXPECT_THROW(table.erase(1), std::runtime_error);
}

TEST(TestTableOnTree, clear_empty_table)
{
    TableOnTree<int, std::string> table;

    table.clear();

    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(TestTableOnTree, clear_non_empty_table)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.clear();

    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.size(), 0);
}

TEST(TestTableOnTree, size_after_multiple_insertions)
{
    TableOnTree<int, std::string> table;

    for (int i = 0; i < 10; i++)
    {
        table.insert(i, "value");
    }

    EXPECT_EQ(table.size(), 10);
}

TEST(TestTableOnTree, size_after_multiple_erasures)
{
    TableOnTree<int, std::string> table;

    for (int i = 0; i < 10; i++)
    {
        table.insert(i, "value");
    }

    table.erase(0);
    table.erase(1);
    table.erase(2);

    EXPECT_EQ(table.size(), 7);
}

TEST(TestTableOnTree, find_returns_reference)
{
    TableOnTree<int, std::string> table;

    table.insert(1, "old");

    table.find(1) = "new";

    EXPECT_EQ(table.find(1), "new");
}

TEST(TestTableOnTree, many_insertions_and_searches)
{
    TableOnTree<int, int> table;

    for (int i = 0; i < 100; i++)
    {
        table.insert(i, i * 10);
    }

    EXPECT_EQ(table.size(), 100);

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(table.find(i), i * 10);
    }
}

TEST(TestTableOnTree, erase_several_elements)
{
    TableOnTree<int, int> table;

    for (int i = 0; i < 20; i++)
    {
        table.insert(i, i);
    }

    table.erase(5);
    table.erase(10);
    table.erase(15);

    EXPECT_FALSE(table.contains(5));
    EXPECT_FALSE(table.contains(10));
    EXPECT_FALSE(table.contains(15));

    EXPECT_EQ(table.size(), 17);
}