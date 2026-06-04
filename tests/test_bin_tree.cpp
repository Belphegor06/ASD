#include <gtest/gtest.h>

#include "../lib_bin_tree/bin_tree.h"

TEST(TestBinaryTree, default_constructor_creates_empty_tree)
{
    BinaryTree<int> tree;

    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(TestBinaryTree, insert_one_element)
{
    BinaryTree<int> tree;

    tree.insert(5);

    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_TRUE(tree.contains(5));
}

TEST(TestBinaryTree, insert_several_elements)
{
    BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(1);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    EXPECT_EQ(tree.size(), 6);

    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_TRUE(tree.contains(4));
}

TEST(TestBinaryTree, insert_duplicate_element_throws_exception)
{
    BinaryTree<int> tree;

    tree.insert(5);

    EXPECT_THROW(tree.insert(5), std::runtime_error);
}

TEST(TestBinaryTree, find_existing_element)
{
    BinaryTree<int> tree;

    tree.insert(10);

    EXPECT_EQ(tree.find(10), 10);
}

TEST(TestBinaryTree, find_non_existing_element_throws_exception)
{
    BinaryTree<int> tree;

    tree.insert(10);

    EXPECT_THROW(tree.find(100), std::runtime_error);
}

TEST(TestBinaryTree, contains_returns_true_for_existing_element)
{
    BinaryTree<int> tree;

    tree.insert(42);

    EXPECT_TRUE(tree.contains(42));
}

TEST(TestBinaryTree, contains_returns_false_for_missing_element)
{
    BinaryTree<int> tree;

    tree.insert(42);

    EXPECT_FALSE(tree.contains(100));
}

TEST(TestBinaryTree, erase_single_element_tree)
{
    BinaryTree<int> tree;

    tree.insert(5);

    tree.erase(5);

    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(TestBinaryTree, erase_leaf)
{
    BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(9);
    tree.insert(1);
    tree.insert(4);
    tree.insert(7);

    tree.erase(4);

    EXPECT_FALSE(tree.contains(4));
    EXPECT_EQ(tree.size(), 5);

    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(9));
}

TEST(TestBinaryTree, erase_node_with_only_left_child)
{
    BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(9);
    tree.insert(1);
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);

    tree.erase(9);

    EXPECT_FALSE(tree.contains(9));

    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_TRUE(tree.contains(8));

    EXPECT_EQ(tree.size(), 7);
}

TEST(TestBinaryTree, erase_node_with_only_right_child)
{
    BinaryTree<int> tree;

    tree.insert(11);
    tree.insert(5);
    tree.insert(13);
    tree.insert(7);
    tree.insert(12);
    tree.insert(15);
    tree.insert(6);
    tree.insert(10);

    tree.erase(5);

    EXPECT_FALSE(tree.contains(5));

    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_TRUE(tree.contains(10));

    EXPECT_EQ(tree.size(), 7);
}

TEST(TestBinaryTree, erase_node_with_two_children)
{
    BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    tree.erase(5);

    EXPECT_FALSE(tree.contains(5));

    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(4));
    EXPECT_TRUE(tree.contains(6));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(8));

    EXPECT_EQ(tree.size(), 6);
}

TEST(TestBinaryTree, erase_root_with_two_children)
{
    BinaryTree<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    tree.erase(50);

    EXPECT_FALSE(tree.contains(50));

    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(30));
    EXPECT_TRUE(tree.contains(40));
    EXPECT_TRUE(tree.contains(60));
    EXPECT_TRUE(tree.contains(70));
    EXPECT_TRUE(tree.contains(80));

    EXPECT_EQ(tree.size(), 6);
}

TEST(TestBinaryTree, erase_non_existing_element_throws_exception)
{
    BinaryTree<int> tree;

    tree.insert(5);

    EXPECT_THROW(tree.erase(100), std::runtime_error);
}

TEST(TestBinaryTree, erase_from_empty_tree_throws_exception)
{
    BinaryTree<int> tree;

    EXPECT_THROW(tree.erase(1), std::runtime_error);
}

TEST(TestBinaryTree, clear_empty_tree)
{
    BinaryTree<int> tree;

    tree.clear();

    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(TestBinaryTree, clear_non_empty_tree)
{
    BinaryTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    tree.clear();

    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(TestBinaryTree, insert_after_clear)
{
    BinaryTree<int> tree;

    tree.insert(1);
    tree.insert(2);

    tree.clear();

    tree.insert(10);

    EXPECT_EQ(tree.size(), 1);
    EXPECT_TRUE(tree.contains(10));
}

TEST(TestBinaryTree, find_returns_reference)
{
    BinaryTree<int> tree;

    tree.insert(5);

    tree.find(5) = 100;

    EXPECT_EQ(tree.find(100), 100);
    EXPECT_FALSE(tree.contains(5));
}

TEST(TestBinaryTree, size_after_many_insertions)
{
    BinaryTree<int> tree;

    for (int i = 0; i < 100; i++)
    {
        tree.insert(i);
    }

    EXPECT_EQ(tree.size(), 100);
}

TEST(TestBinaryTree, size_after_many_erasures)
{
    BinaryTree<int> tree;

    for (int i = 0; i < 20; i++)
    {
        tree.insert(i);
    }

    for (int i = 0; i < 10; i++)
    {
        tree.erase(i);
    }

    EXPECT_EQ(tree.size(), 10);
}

TEST(TestBinaryTree, tree_remains_correct_after_many_operations)
{
    BinaryTree<int> tree;

    for (int i = 0; i < 50; i++)
    {
        tree.insert(i);
    }

    tree.erase(10);
    tree.erase(20);
    tree.erase(30);

    EXPECT_FALSE(tree.contains(10));
    EXPECT_FALSE(tree.contains(20));
    EXPECT_FALSE(tree.contains(30));

    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.contains(25));
    EXPECT_TRUE(tree.contains(35));

    EXPECT_EQ(tree.size(), 47);
}