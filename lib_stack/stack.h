#pragma once
#include "..\lib_tvector\tvector.h"
#include <stdexcept>

template <class T>
class TStack {
private:
    TVector<T> _data;

public:
    // Добавление элемента на вершину стека
    void push(const T& value) {
        _data.push_back(value);
    }

    // Удаление верхнего элемента
    void pop() {
        if (is_empty())
            throw std::out_of_range("Stack is empty");
        _data.pop_back();
    }

    // Доступ к верхнему элементу
    T& top() {
        if (is_empty())
            throw std::out_of_range("Stack is empty");
        return _data.back();
    }

    const T& top() const {
        if (is_empty())
            throw std::out_of_range("Stack is empty");
        return _data.back();
    }

    // Проверка на пустоту
    bool is_empty() const {
        return _data.is_empty();
    }

    // Очистка стека
    void clear() {
        _data.clear();
    }

    // Количество элементов
    size_t size() const {
        return _data.size();
    }
};

