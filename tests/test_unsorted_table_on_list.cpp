#include <gtest/gtest.h>
#include "../lib_unsorted_table_on_list/unsorted_table_on_list.h"

TEST(TestUnsortedTableOnList, the_exception_is_when_insert_not_a_unique_key) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");


    ASSERT_ANY_THROW(t1.insert(3, "Third"));
}

TEST(TestUnsortedTableOnList, check_the_insert_after_erase) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(2);
    t1.insert(4, "Fourth");


    EXPECT_EQ(t1.find(4), "Fourth");
}

TEST(TestUnsortedTableOnList, check_the_erase) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");
    t1.erase(1);


    ASSERT_ANY_THROW(t1.find(1));
}

TEST(TestUnsortedTableOnList, the_exception_is_when_deleting_by_a_key_that_does_not_exist) {
    UnsortedTableOnList<int, std::string> t1;

    t1.insert(1, "First");
    t1.insert(2, "Second");
    t1.insert(3, "Third");


    ASSERT_ANY_THROW(t1.erase(5));
}

TEST(TestUnsortedTableOnList, check_the_key_find) {
    UnsortedTableOnList<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");


    EXPECT_EQ(t1.find("r974"), "when");
}

TEST(TestUnsortedTableOnList, the_exception_is_when_the_key_is_not_found) {
    UnsortedTableOnList<std::string, std::string> t1;

    t1.insert("r123", "what");
    t1.insert("r567", "where");
    t1.insert("r974", "when");


    ASSERT_ANY_THROW(t1.find("r1024"));
}

TEST(TestUnsortedTableOnList, check_an_empty_Table) {
    UnsortedTableOnList<double, std::string> t1;

    t1.insert(1.5, "it is double");
    t1.erase(1.5);


    EXPECT_TRUE(t1.empty());
}

TEST(TestUnsortedTableOnList, check_a_non_empty_itable) {
    UnsortedTableOnList<double, std::string> t1;

    t1.insert(1.5, "it is double");


    EXPECT_FALSE(t1.empty());
}
