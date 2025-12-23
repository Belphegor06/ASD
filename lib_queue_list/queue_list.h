#pragma once
#include <stdexcept>
#include "..\lib_list\list.h"

template <class T>
class QueueList {
private:
    List<T> _list;

public:
    QueueList() = default;

    // Добавление элемента в конец очереди
    void push(const T& value) {
        _list.push_back(value);
    }

    // Удаление первого элемента очереди
    void pop() {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        _list.pop_front();
    }

    // Первый элемент очереди
    T& front() {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        return _list.front();
    }

    const T& front() const {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        return _list.front();
    }

    // Последний элемент очереди
    T& back() {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        return _list.back();
    }

    const T& back() const {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        return _list.back();
    }

    // Проверка на пустоту
    bool is_empty() const {
        return _list.is_empty();
    }

    // Очистка очереди
    void clear() {
        while (!is_empty())
            pop();
    }
};
