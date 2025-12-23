#pragma once
#include <stdexcept>

template <class T>
class TQueue {
private:
    T* _data;   // Указатель на массив элементов
    size_t _capacity;   // Общая вместимость массива
    size_t _size;   // Текущее количество элементов
    size_t _front;   // Индекс первого элемента в очереди
    size_t _back;   // Индекс следующего свободного места для добавления
    size_t DEFAULT_CAPACITY = 10;   // Начальный размер буфера по умолчанию

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];  // Создаем новый массив
        // Копируем элементы сохраняя порядок (от front до back)
        for (size_t i = 0; i < _size; i++)
            new_data[i] = _data[(_front + i) % _capacity];
        delete[] _data;
        _data = new_data;   // Обновляем указатель
        _capacity = new_capacity;   // Обновляем емкость
        _front = 0;   // Сбрасываем указатель начала
        _back = _size;   // Указываем на следующую свободную позицию
    }

public:
    // Конструктор с параметром начальной емкости
    TQueue(size_t capacity = DEFAULT_CAPACITY)
    {
        _capacity = capacity;
        _size = 0;
        _front = 0;  // Очередь начинается с начала массива
        _back = 0;   // Следующий элемент будет добавлен в начало
        _data = new T[_capacity]; // Выделяем память
    }

    // Деструктор - освобождаем память
    ~TQueue() {
        delete[] _data;
    }

    // Добавление элемента в конец очереди
    void push(const T& value) {
        if (_size == _capacity)  // Если нет свободного места
            reallocate(_capacity * 2); // Увеличиваем буфер в 2 раза

        _data[_back] = value;          // Добавляем элемент
        _back = (_back + 1) % _capacity; // Циклически перемещаем указатель
        _size++;                       // Увеличиваем счетчик элементов
    }

    // Удаление первого элемента из очереди
    void pop() {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        _front = (_front + 1) % _capacity; // Циклически сдвигаем указатель начала
        _size--;                           // Уменьшаем счетчик элементов
    }

    // Получение ссылки на первый элемент (неконстантная версия)
    T& front() {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        return _data[_front];
    }

    // Получение константной ссылки на первый элемент
    const T& front() const {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        return _data[_front];
    }

    // Получение ссылки на последний элемент (неконстантная версия)
    T& back() {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        // Вычисляем индекс последнего элемента с учетом цикличности
        size_t index = (_back == 0 ? _capacity - 1 : _back - 1);
        return _data[index];
    }

    // Получение константной ссылки на последний элемент
    const T& back() const {
        if (is_empty())
            throw std::out_of_range("Queue is empty");
        size_t index = (_back == 0 ? _capacity - 1 : _back - 1);
        return _data[index];
    }

    // Получение текущего количества элементов в очереди
    size_t size() const {
        return _size;
    }

    // Проверка очереди на пустоту
    bool is_empty() const {
        return _size == 0;
    }

    // Очистка очереди (без освобождения памяти)
    void clear() {
        _size = 0;   // Сбрасываем счетчик элементов
        _front = 0;   // Сбрасываем указатель начала
        _back = 0;   // Сбрасываем указатель конца
    }
};