#include <gtest/gtest.h>
#include "../lib_tree/tree.h"

TEST(TestTree, default_constructor_creates_empty_tree)
{
    Tree<int> tree;

    EXPECT_TRUE(tree.empty());
}

TEST(TestTree, insert_one_element)
{
    Tree<int> tree;

    tree.insert(5);

    EXPECT_FALSE(tree.empty());
    EXPECT_TRUE(tree.find(5));
}

TEST(TestTree, insert_several_elements)
{
    Tree<int> tree;

    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(7));
    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(4));
}

TEST(TestTree, find_existing_element_returns_true)
{
    Tree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    EXPECT_TRUE(tree.find(20));
}

TEST(TestTree, find_non_existing_element_returns_false)
{
    Tree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    EXPECT_FALSE(tree.find(100));
}

TEST(TestTree, erase_leaf_element)
{
    Tree<int> tree;

    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    tree.erase(7);

    EXPECT_FALSE(tree.find(7));

    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(4));
    EXPECT_TRUE(tree.find(5));
}

TEST(TestTree, erase_root_element)
{
    Tree<int> tree;

    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    tree.erase(5);

    EXPECT_FALSE(tree.find(5));

    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(4));
    EXPECT_TRUE(tree.find(7));
}

TEST(TestTree, erase_only_element)
{
    Tree<int> tree;

    tree.insert(100);

    tree.erase(100);

    EXPECT_TRUE(tree.empty());
}

TEST(TestTree, erase_from_empty_tree_throws_exception)
{
    Tree<int> tree;

    EXPECT_THROW(tree.erase(5), std::runtime_error);
}

TEST(TestTree, erase_non_existing_element_throws_exception)
{
    Tree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    EXPECT_THROW(tree.erase(100), std::runtime_error);
}

TEST(TestTree, duplicate_values_can_be_found)
{
    Tree<int> tree;

    tree.insert(5);
    tree.insert(5);
    tree.insert(5);

    EXPECT_TRUE(tree.find(5));
}

TEST(TestTree, erase_one_of_duplicate_values)
{
    Tree<int> tree;

    tree.insert(5);
    tree.insert(5);
    tree.insert(5);

    tree.erase(5);

    EXPECT_TRUE(tree.find(5));
}

TEST(TestTree, tree_remains_correct_after_multiple_erasures)
{
    Tree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    tree.erase(6);
    tree.erase(5);
    tree.erase(4);

    EXPECT_TRUE(tree.find(1));
    EXPECT_TRUE(tree.find(2));
    EXPECT_TRUE(tree.find(3));

    EXPECT_FALSE(tree.find(4));
    EXPECT_FALSE(tree.find(5));
    EXPECT_FALSE(tree.find(6));
}