//#include <gtest/gtest.h>
//#include <iostream>
//#include "../lib_sorted_table_on_arr/sorted_table_on_arr.h"
//
//TEST(TestSortedTableOnArr, can_insert_element) {
//    SortedTableOnArr<int, int> table;
//    ASSERT_NO_THROW(table.insert(1, 10));
//}
//
//TEST(TestSortedTableOnArr, can_insert_elements_and_keep_sorted) {
//    SortedTableOnArr<int, int> table;
//
//    table.insert(5, 50);
//    table.insert(1, 10);
//    table.insert(3, 30);
//
//    EXPECT_EQ(1, table.getRow(0).key);
//    EXPECT_EQ(3, table.getRow(1).key);
//    EXPECT_EQ(5, table.getRow(2).key);
//}
//
//TEST(TestSortedTableOnArr, insert_increases_size) {
//    SortedTableOnArr<int, int> table;
//
//    table.insert(1, 10);
//
//    EXPECT_EQ(1, table.size());
//}
//
//TEST(TestSortedTableOnArr, can_find_inserted_element) {
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//
//    int actual = table.find(1);
//
//    EXPECT_EQ(10, actual);
//}
//
//TEST(TestSortedTableOnArr, contains_returns_true_for_existing_key) {
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//
//    EXPECT_TRUE(table.contains(1));
//}
//
//TEST(TestSortedTableOnArr, contains_returns_false_for_missing_key) {
//    SortedTableOnArr<int, int> table;
//
//    EXPECT_FALSE(table.contains(5));
//}
//
//TEST(TestSortedTableOnArr, table_is_empty_after_creation) {
//    SortedTableOnArr<int, int> table;
//
//    EXPECT_TRUE(table.empty());
//}
//
//TEST(TestSortedTableOnArr, table_is_not_empty_after_insert) {
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//
//    EXPECT_FALSE(table.empty());
//}
//
//TEST(TestSortedTableOnArr, can_erase_existing_key) {
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//
//    ASSERT_NO_THROW(table.erase(1));
//}
//
//TEST(TestSortedTableOnArr, erase_reduces_size) {
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//
//    table.erase(1);
//
//    EXPECT_EQ(0, table.size());
//}
//
//TEST(TestSortedTableOnArr, erase_keeps_sorted_order) {
//    SortedTableOnArr<int, int> table;
//
//    table.insert(5, 50);
//    table.insert(1, 10);
//    table.insert(3, 30);
//
//    table.erase(3);
//
//    EXPECT_EQ(1, table.getRow(0).key);
//    EXPECT_EQ(5, table.getRow(1).key);
//}
//
//TEST(TestSortedTableOnArr, clear_makes_table_empty) {
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//    table.insert(2, 20);
//
//    table.clear();
//
//    EXPECT_TRUE(table.empty());
//}
//
//TEST(TestSortedTableOnArr, ignore_when_insert_duplicate_key)
//{
//    SortedTableOnArr<int, int> table;
//    table.insert(1, 10);
//
//    // повторная вставка НЕ должна менять значение и НЕ должна бросать исключение
//    ASSERT_NO_THROW(table.insert(1, 20));
//
//    // значение должно остаться прежним
//    ASSERT_EQ(table.find(1), 10);
//
//    // размер не должен увеличиться
//    ASSERT_EQ(table.size(), 1);
//}
//
//TEST(TestSortedTableOnArr, throw_when_find_non_existing_key) {
//    SortedTableOnArr<int, int> table;
//
//    ASSERT_THROW(table.find(5), std::out_of_range);
//}
//
//TEST(TestSortedTableOnArr, throw_when_erase_non_existing_key) {
//    SortedTableOnArr<int, int> table;
//
//    ASSERT_THROW(table.erase(5), std::out_of_range);
//}
//
//TEST(TestSortedTableOnVector, insert_increases_size) {
//    SortedTableOnArr<int, int> t;
//
//    t.insert(1, 10);
//    t.insert(2, 20);
//
//    EXPECT_EQ(2, t.size());
//}
//
//TEST(TestSortedTableOnVector, elements_are_sorted) {
//    SortedTableOnArr<int, int> t;
//
//    t.insert(5, 50);
//    t.insert(1, 10);
//    t.insert(3, 30);
//
//    EXPECT_EQ(1, t.getRow(0).key);
//    EXPECT_EQ(3, t.getRow(1).key);
//    EXPECT_EQ(5, t.getRow(2).key);
//}
//
//TEST(TestSortedTableOnVector, contains_works_correctly) {
//    SortedTableOnArr<int, int> t;
//
//    t.insert(1, 10);
//
//    EXPECT_TRUE(t.contains(1));
//    EXPECT_FALSE(t.contains(5));
//}
//
//TEST(TestSortedTableOnVector, clear_works) {
//    SortedTableOnArr<int, int> t;
//
//    t.insert(1, 10);
//    t.insert(2, 20);
//
//    t.clear();
//
//    EXPECT_TRUE(t.empty());
//}