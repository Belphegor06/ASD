#pragma once
#include <stdexcept>
#include "..\lib_list\list.h"

template <class T>
class StackList {
private:
    List<T> _list;

public:
    StackList() = default;

    // Добавление элемента на вершину стека
    void push(const T& value) {
        _list.push_back(value);
    }

    // Удаление верхнего элемента
    void pop() {
        if (is_empty())
            throw std::out_of_range("Stack is empty");
        _list.pop_back();
    }

    // Доступ к верхнему элементу
    T& top() {
        if (is_empty())
            throw std::out_of_range("Stack is empty");
        return _list.back();
    }

    const T& top() const {
        if (is_empty())
            throw std::out_of_range("Stack is empty");
        return _list.back();
    }

    // Проверка на пустоту
    bool is_empty() const {
        return _list.is_empty();
    }

    // Очистка стека
    void clear() {
        while (!is_empty())
            pop();
    }
};
