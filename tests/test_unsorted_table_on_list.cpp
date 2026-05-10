#include <gtest/gtest.h>
#include "../lib_unsorted_table_on_arr/unsorted_table_on_arr.h"

TEST(TestUnsortedTableOnArr, can_insert_element) {
    // Arrange
    UnsortedTableOnArr<int, int> table;

    // Act & Assert
    ASSERT_NO_THROW(table.insert(1, 10));
}

TEST(TestUnsortedTableOnArr, insert_increases_size) {
    // Arrange
    UnsortedTableOnArr<int, int> table;

    // Act
    table.insert(1, 10);

    // Assert
    EXPECT_EQ(1, table.size());
}

TEST(TestUnsortedTableOnArr, can_find_inserted_element) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);

    // Act
    int actual = table.find(1);

    // Assert
    int expected = 10;
    EXPECT_EQ(expected, actual);
}

TEST(TestUnsortedTableOnArr, contains_returns_true_for_existing_key) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);

    // Act
    bool actual = table.contains(1);

    // Assert
    EXPECT_TRUE(actual);
}

TEST(TestUnsortedTableOnArr, contains_returns_false_for_missing_key) {
    // Arrange
    UnsortedTableOnArr<int, int> table;

    // Act
    bool actual = table.contains(5);

    // Assert
    EXPECT_FALSE(actual);
}

TEST(TestUnsortedTableOnArr, table_is_empty_after_creation) {
    // Arrange
    UnsortedTableOnArr<int, int> table;

    // Act
    bool actual = table.empty();

    // Assert
    EXPECT_TRUE(actual);
}

TEST(TestUnsortedTableOnArr, table_is_not_empty_after_insert) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);

    // Act
    bool actual = table.empty();

    // Assert
    EXPECT_FALSE(actual);
}

TEST(TestUnsortedTableOnArr, can_erase_existing_key) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);

    // Act & Assert
    ASSERT_NO_THROW(table.erase(1));
}

TEST(TestUnsortedTableOnArr, erase_reduces_size) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);

    // Act
    table.erase(1);

    // Assert
    EXPECT_EQ(0, table.size());
}

TEST(TestUnsortedTableOnArr, clear_makes_table_empty) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);

    // Act
    table.clear();

    // Assert
    EXPECT_TRUE(table.empty());
}

TEST(TestUnsortedTableOnArr, throw_when_insert_duplicate_key) {
    // Arrange
    UnsortedTableOnArr<int, int> table;
    table.insert(1, 10);

    // Act & Assert
    ASSERT_THROW(table.insert(1, 20), std::logic_error);
}

TEST(TestUnsortedTableOnArr, throw_when_find_non_existing_key) {
    // Arrange
    UnsortedTableOnArr<int, int> table;

    // Act & Assert
    ASSERT_THROW(table.find(5), std::out_of_range);
}

TEST(TestUnsortedTableOnArr, throw_when_erase_non_existing_key) {
    // Arrange
    UnsortedTableOnArr<int, int> table;

    // Act & Assert
    ASSERT_THROW(table.erase(5), std::out_of_range);
}