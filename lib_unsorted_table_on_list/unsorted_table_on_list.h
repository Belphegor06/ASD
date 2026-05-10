#pragma once

#include <iostream>
#include <stdexcept>

#include "../lib_itable/itable.h"
#include "../lib_list/list.h"

template <class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {
    List<std::pair<TKey, TValue>> _rows;

public:
    UnsortedTableOnList() = default;
    UnsortedTableOnList(const UnsortedTableOnList&) = default;
    ~UnsortedTableOnList() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;

    bool contains(const TKey& key) const override;
    size_t size() const override;
    bool empty() const override;
    void clear() override;

    void print() const override;

private:
    Node<std::pair<TKey, TValue>>* find_position(const TKey& key);
    const Node<std::pair<TKey, TValue>>* find_position(const TKey& key) const;

    size_t _size = 0;
};


template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (find_position(key) != nullptr) {
        throw std::logic_error("The key is not unique!");
    }

    _rows.push_back(std::make_pair(key, value));
    ++_size;
}


template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    Node<std::pair<TKey, TValue>>* node = find_position(key);

    if (node == nullptr) {
        throw std::logic_error("Key not found for erase!");
    }

    _rows.erase(node);
    --_size;
}


template <class TKey, class TValue>
TValue& UnsortedTableOnList<TKey, TValue>::find(const TKey& key) {
    Node<std::pair<TKey, TValue>>* node = find_position(key);

    if (node == nullptr) {
        throw std::logic_error("Key not found!");
    }

    return node->value.second;
}


template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::contains(const TKey& key) const {
    return find_position(key) != nullptr;
}


template <class TKey, class TValue>
size_t UnsortedTableOnList<TKey, TValue>::size() const {
    return _size;
}


template <class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::empty() const {
    return _size == 0;
}


template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::clear() {
    while (!_rows.empty()) {
        _rows.pop_front();
    }

    _size = 0;
}


template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::print() const {
    std::cout << "UnsortedTableOnList:\n";

    const Node<std::pair<TKey, TValue>>* cur = _rows.front_node();

    while (cur != nullptr) {
        std::cout << "| "
            << cur->value.first
            << " | "
            << cur->value.second
            << " |\n";

        cur = cur->next;
    }
}


template <class TKey, class TValue>
Node<std::pair<TKey, TValue>>*
UnsortedTableOnList<TKey, TValue>::find_position(const TKey& key) {
    Node<std::pair<TKey, TValue>>* cur = _rows.front_node();

    while (cur != nullptr) {
        if (cur->value.first == key) {
            return cur;
        }

        cur = cur->next;
    }

    return nullptr;
}

template <class TKey, class TValue>
const Node<std::pair<TKey, TValue>>*
UnsortedTableOnList<TKey, TValue>::find_position(const TKey& key) const {
    const Node<std::pair<TKey, TValue>>* cur = _rows.front_node();

    while (cur != nullptr) {
        if (cur->value.first == key) {
            return cur;
        }

        cur = cur->next;
    }

    return nullptr;
}


template <class TKey, class TValue>
std::ostream& operator<<(std::ostream& out,
    const Table<TKey, TValue>& table) {
    table.print();
    return out;
}