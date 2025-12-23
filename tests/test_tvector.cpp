#include <gtest/gtest.h>
#include "../lib_tvector/TVector.h"

TEST(TVectorConstructor, constructor_with_capacity) {
    TVector<int> vec(5);
    EXPECT_EQ(20u, vec.capacity()); // 5 + DEFAULT_CAPACITY(15)
}

TEST(TVectorConstructor, initializer_list_constructor) {
    TVector<int> vec = { 10, 20, 30 };

    EXPECT_EQ(10, vec[0]);
    EXPECT_EQ(20, vec[1]);
    EXPECT_EQ(30, vec[2]);
    EXPECT_EQ(3u, vec.size());
}

TEST(TVectorConstructor, copy_constructor) {
    TVector<int> original = { 1, 2, 3 };
    TVector<int> copy(original);

    EXPECT_EQ(original, copy);
}

TEST(TVectorConstructor, assignment_operator) {
    TVector<int> a = { 1, 2, 3 };
    TVector<int> b;

    b = a;
    EXPECT_EQ(a, b);
}


TEST(TVectorAccess, access_erased_element) {
    TVector<int> vec = { 10, 20, 30 };
    vec.erase(1);

    ASSERT_NO_THROW(vec.at(1));
    EXPECT_EQ(30, vec.at(1));
}

TEST(TVectorAccess, operator_access) {
    TVector<int> vec;
    vec.push_back(42);

    EXPECT_EQ(42, vec[0]);
    EXPECT_EQ(1u, vec.size());
}

TEST(TVectorAccess, front_back) {
    TVector<int> vec;
    vec.push_back(100);
    vec.push_back(200);

    EXPECT_EQ(100, vec.front());
    EXPECT_EQ(200, vec.back());
}

TEST(TVectorAccess, front_back_after_clear) {
    TVector<int> vec = { 10, 20, 30 };
    vec.clear();

    EXPECT_THROW(vec.front(), std::out_of_range);
    EXPECT_THROW(vec.back(), std::out_of_range);
}


TEST(TVectorPush, reuse_deleted_slot) {
    TVector<int> vec = { 1, 2, 3 };
    vec.erase(1);

    size_t old_size = vec.size();
    vec.push_back(4);

    EXPECT_EQ(4, vec[2]);
    EXPECT_EQ(old_size + 1, vec.size());
}

TEST(TVectorPush, push_front_on_deleted) {
    TVector<int> v = { 1, 2, 3 };
    v.erase(0);

    size_t old_size = v.size();
    v.push_front(99);

    EXPECT_EQ(99, v.front());
    EXPECT_EQ(old_size + 1, v.size());
}

TEST(TVectorPush, push_front_from_zero) {
    TVector<int> v;
    for (int i = 0; i < 5; i++)
        v.push_back(i);

    int old_front = v.front();
    v.push_front(999);

    EXPECT_EQ(999, v.front());
    EXPECT_EQ(old_front, v.at(1));
}

TEST(TVectorPush, double_push_front_on_full) {
    TVector<int> v;
    for (int i = 0; i < 14; i++)
        v.push_back(i);

    int old_front = v.front();
    v.push_front(100);
    v.push_front(200);

    EXPECT_EQ(200, v.front());
    EXPECT_EQ(100, v.at(1));
    EXPECT_EQ(old_front, v.at(2));
}

TEST(TVectorPush, push_back_on_deleted) {
    TVector<int> v = { 1, 2, 3 };
    v.erase(2);

    size_t old_size = v.size();
    v.push_back(99);

    EXPECT_EQ(99, v.back());
    EXPECT_EQ(old_size + 1, v.size());
}


TEST(TVectorPop, pop_front) {
    TVector<int> v = { 1, 2, 3 };
    v.pop_front();

    EXPECT_EQ(2, v.size());
    EXPECT_EQ(2, v[0]);
    EXPECT_EQ(3, v[1]);
}

TEST(TVectorPop, pop_back) {
    TVector<int> v = { 1, 2, 3 };
    v.pop_back();

    EXPECT_EQ(2u, v.size());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(-1, find_last(v, [](int x) { return x == 3; }));
}


TEST(TVectorErase, erase_first) {
    TVector<int> v = { 10, 20, 30 };
    v.erase(0);

    EXPECT_EQ(2u, v.size());
    EXPECT_EQ(20, v[0]);
    EXPECT_EQ(30, v[1]);
}

TEST(TVectorErase, erase_last) {
    TVector<int> v = { 10, 20, 30 };
    v.erase(2);

    EXPECT_EQ(2u, v.size());
    EXPECT_EQ(10, v[0]);
    EXPECT_EQ(20, v[1]);
}

TEST(TVectorErase, erase_from_empty) {
    TVector<int> vec;
    EXPECT_THROW(vec.erase(0), std::out_of_range);
}


TEST(TVectorInsert, insert_middle) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(3);

    vec.insert(1, 2);

    EXPECT_EQ(3u, vec.size());
    EXPECT_EQ(2, vec[1]);
}

TEST(TVectorInsert, insert_at_begin) {
    TVector<int> vec = { 2, 3, 4 };
    vec.insert(0, 1);

    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(4u, vec.size());
}

TEST(TVectorInsert, insert_at_end) {
    TVector<int> vec = { 1, 2, 3 };
    vec.insert(3, 4);

    EXPECT_EQ(4, vec[3]);
    EXPECT_EQ(4u, vec.size());
}


TEST(TVectorClear, clear_and_reuse) {
    TVector<int> vec = { 1, 2, 3 };
    vec.clear();
    vec.push_back(10);

    EXPECT_EQ(1u, vec.size());
    EXPECT_EQ(10, vec[0]);
}

TEST(TVectorCapacity, capacity_grows) {
    TVector<int> vec;
    size_t cap = vec.capacity();

    for (int i = 0; i < 100; i++)
        vec.push_back(i);

    EXPECT_GT(vec.capacity(), cap);
}

TEST(TVectorCapacity, shrink_to_fit) {
    TVector<int> vec = { 1,2,3,4,5,6,7,8,9,0 };
    vec.pop_back();
    vec.pop_back();
    vec.shrink_to_fit();

    EXPECT_EQ(8u, vec.capacity());
}


TEST(TVectorFind, find_all) {
    TVector<int> vec = { 1, 2, 1, 3, 1 };

    auto indices = find_all(vec, [](int x) { return x == 1; });

    ASSERT_EQ(3u, indices.size());
    EXPECT_EQ(0u, indices[0]);
    EXPECT_EQ(2u, indices[1]);
    EXPECT_EQ(4u, indices[2]);
}


TEST(TVectorInfo, is_empty) {
    TVector<int> vec;
    EXPECT_TRUE(vec.is_empty());
    EXPECT_EQ(0u, vec.size());
}

TEST(TVectorInfo, get_size) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    EXPECT_EQ(2u, vec.size());
}
