#pragma once

// TVector<int> v(3) создаёт вектор вместимостью 3 + DEFAULT_CAPACITY (15), 3 ячейки заполнены

//#include <functional>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <ctime>

//#define DEFAULT_CAPACITY = 15; не робит почемута
enum State { empty, busy, deleted }; // тип данных, который может принимать только перечисленные данные (классная шняга)

template <class T>
class TVector
{
private:
    T* _data; // указатель на массив
    State* _states; // массив статусов
    size_t _capacity; // общий размер           size_t это целочисленный беззнаковый тип данных. удобно чтобы не писать unsigned int или short каждый раз.
    size_t _size; // размер занятых ячеек
    size_t _deleted; // кол-во удалённых ячеек
    static constexpr size_t DEFAULT_CAPACITY = 15; // как #define только с определённым типом видно только в классе и с этим работает

    // функция перевыделения памяти: копирует только активные элементы (busy)
    void reallocate(size_t new_capacity)
    {
        T* new_data = new T[new_capacity]; // создаём новый массив
        State* new_states = new State[new_capacity]; // создаём массив состояний
        size_t index = 0;
        for (size_t i = 0; i < _capacity; i++)
            if (_states[i] == busy)
            {
                new_data[index] = _data[i]; // копируем данные
                new_states[index] = busy; // ставим статус busy
                index++;
            }
        for (size_t i = index; i < new_capacity; i++)
            new_states[i] = empty; // остальные ячейки — пустые
        delete[] _data; // освобождаем старую память
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = new_capacity;
        _size = index;
        _deleted = 0;
    }

    // проверка заполнености массива
    bool is_full() const
    {
        return _size + _deleted == _capacity;
    }

    // отвечает за обеспечение достаточной вместимости массива под заданное количество элементов
    void ensure_capacity() {
        if (is_full()) {
            reallocate(_capacity + DEFAULT_CAPACITY);
        }
    }

    bool need_realocate()
    {
        if (_deleted * 100 / _capacity > 15) return 1;
        return 0;
    }

    size_t real_pos(size_t pos)
    {
        size_t busy_count = 0;
        size_t realpos = 0;
        for (; realpos < _capacity; realpos++)
            if (_states[realpos] == busy)
            {
                if (busy_count == pos) break;
                busy_count++;
            }
        return realpos;
    }

public:
    State* states() { return _states; }
    const State* states() const { return _states; }

    // вектор по умолчанию и вектор с заданным значением
    TVector(size_t size = 0)
    {
        _capacity = size + DEFAULT_CAPACITY;
        _size = 0;
        _deleted = 0;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; i++)
            if (i < size)
                _states[i] = busy;
            else
                _states[i] = empty;
        _size = size;
    }

    // конструктор копирования
    TVector(const TVector<T>& other)
    {
        _capacity = other._capacity;
        _size = other._size;
        _deleted = other._deleted;

        _data = new T[_capacity];
        _states = new State[_capacity];

        for (size_t i = 0; i < _capacity; i++)
        {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
    }

    // заполняет вектор значениями из {} при создании объекта
    TVector(std::initializer_list<T> init)
    {
        _capacity = init.size() + DEFAULT_CAPACITY;
        _size = 0;
        _deleted = 0;

        _data = new T[_capacity];
        _states = new State[_capacity];

        size_t i = 0;
        for (auto it = init.begin(); it != init.end(); ++it, ++i) {
            _data[i] = *it;
            _states[i] = busy;
            _size++;
        }

        for (; i < _capacity; i++)
            _states[i] = empty;
    }


    ~TVector() {
        delete[] _data;
        delete[] _states;
    }

    TVector<T>& operator=(const TVector<T>& other)
    {
        if (this != &other)
        {
            delete[] _data;
            delete[] _states;
            _capacity = other._capacity;
            _size = other._size;
            _deleted = other._deleted;
            _data = new T[_capacity];
            _states = new State[_capacity];
            for (size_t i = 0; i < _capacity; ++i)
            {
                _data[i] = other._data[i];
                _states[i] = other._states[i];
            }
        }
        return *this;
    }

    T& operator[](size_t index)
    {
        if (index >= _size) throw std::out_of_range("Index out of range");
        size_t count = 0;
        for (size_t i = 0; i < _capacity; i++)
            if (_states[i] == busy)
            {
                if (count == index)
                    return _data[i];
                count++;
            }
        throw std::out_of_range("Index not found");
    }
    const T& operator[](size_t index) const
    {
        if (index >= _size) throw std::out_of_range("Index out of range");
        size_t count = 0;
        for (size_t i = 0; i < _capacity; i++)
            if (_states[i] == busy)
            {
                if (count == index)
                    return _data[i];
                count++;
            }
        throw std::out_of_range("Index not found");

    }

    bool operator==(const TVector<T>& other) const
    {
        if (_size != other._size) return false; // если количество занятых элементов разное — сразу false
        for (size_t i = 0, j = 0; i < _capacity && j < other._capacity;)
        {
            // пропускаем все "дырки" (элементы, не равные busy) в текущем векторе
            while (i < _capacity && _states[i] != busy) i++;
            // пропускаем все "дырки" во втором векторе
            while (j < other._capacity && other._states[j] != busy) j++;
            if (i < _capacity && j < other._capacity) {
                if (_data[i] != other._data[j]) return false;
                i++; j++;
            }
        }
        return true;
    }

    bool operator!=(const TVector<T>& other) const
    {
        return !(*this == other);
    }

    // возвращает указатель на первый элемент массива внутри TVector
    T* data() { return _data; }
    // возвращает константный указатель на первый элемент массива
    const T* data() const { return _data; }
    // возвращает текущее количество элементов, хранящихся в векторе (busy)
    size_t size() const { return _size; }
    // размер выделенного буфера
    size_t capacity() const { return _capacity; }
    // проверка вектора на пустоту
    bool is_empty() const { return _size == 0; }

    // возвращает первый занятый (busy) элемент вектора
    T& front()
    {
        for (size_t i = 0; i < _capacity; i++)
            if (_states[i] == busy) return _data[i];
        throw std::out_of_range("Vector is empty");
    }
    // возвращает последний занятый (busy) элемент вектора
    T& back()
    {
        for (size_t i = _capacity - 1; i != size_t(-1); i--)
            if (_states[i] == busy)
                return _data[i];
        throw std::out_of_range("Vector is empty");
    }

    const T& back() const
    {
        for (size_t i = _capacity - 1; i != size_t(-1); i--)
            if (_states[i] == busy)
                return _data[i];
        throw std::out_of_range("Vector is empty");
    }


    // возвращает указатель на первый элемент буфера _data
    T* begin() { return _data; }
    // возвращает указатель за последнюю ячейку буфера (_data + _capacity)
    T* end() { return _data + _capacity; }

    // вставка в конец
    void push_back(const T& val)
    {
        ensure_capacity();

        // если всё пусто (вектор пустой)
        if (is_empty())
        {
            _data[0] = val;
            _states[0] = busy;
            _size++;
            return;
        }

        for (size_t i = _size + _deleted - 1; i != size_t(-1); i--)
        {
            if (_states[i] == busy)
            {
                _data[i + 1] = val;
                if (_states[i + 1] == deleted) _deleted--;
                _states[i + 1] = busy;
                _size++;
                return;
            }
            if (_states[i] == deleted)
            {
                _deleted--;
                _states[i] = empty;
            }
        }
    }

    // вставка в начало
    void push_front(const T& val)
    {
        ensure_capacity();

        // если всё пусто (вектор пустой)
        if (is_empty())
        {
            _data[0] = val;
            _states[0] = busy;
            _size++;
            return;
        }

        if (_states[0] == deleted)
            for (size_t i = 0; i < _capacity - 1; i++)
                if (_states[i + 1] == busy)
                {
                    _data[i] = val;
                    _states[i] = busy;
                    _size++;
                    _deleted--;
                    return;
                }

        T a = _data[0];
        State as = _states[0];
        for (size_t i = 1; i < _size + _deleted - 1; i++)
        {
            if (_states[i] == empty || _states[i] == deleted)
            {
                if (_states[i] == deleted) _deleted--;
                break;
            }
            T b = _data[i];
            _data[i] = a;
            a = b;
            State bs = _states[i];
            _states[i] = as;
            as = bs;
        }
        _data[0] = val;
        _states[0] = busy;
        _size++;
    }

    // вставка на позицию
    void insert(size_t pos, const T& val)
    {
        if (pos < 0) throw std::out_of_range("Position should be >= 0");
        if (pos > _size) throw std::out_of_range("Insert position out of range");

        ensure_capacity();

        if (pos == _size)
        {
            push_back(val);
            return;
        }

        if (pos == 0)
        {
            push_front(val);
            return;
        }

        size_t realpos = real_pos(pos);

        // Если ячейка пустая или удалённая — вставляем
        if (_states[realpos - 1] == empty || _states[realpos - 1] == deleted)
        {
            if (_states[realpos - 1] == deleted) _deleted--;
            _data[realpos] = val;
            _states[realpos] = busy;
            _size++;
            return;
        }

        T a = _data[realpos];
        State as = _states[realpos];
        for (size_t i = realpos; i < _size + _deleted - 1; i++)
        {
            if (_states[i] == empty || _states[i] == deleted)
            {
                if (_states[i] == deleted) _deleted--;
                break;
            }
            T b = _data[i];
            _data[i] = a;
            a = b;
            State bs = _states[i];
            _states[i] = as;
            as = bs;
        }
        _data[realpos] = val;
        _states[realpos] = busy;
        _size++;
    }

    // удаление с конца
    void pop_back()
    {
        if (_size == 0) throw std::out_of_range("The vector is empty");
        for (int i = _size + _deleted - 1; i >= 0; i--)
        {
            if (_states[i] == busy)
            {
                _states[i] = empty;
                _size--;
                return;
            }
            if (_states[i] == deleted)
            {
                _states[i] = empty;
                _deleted--;
            }
        }
    }

    // удаление в начале
    void pop_front()
    {
        if (_size == 0)
            throw std::runtime_error("Vector is empty");

        for (size_t i = 0; i < _size + _deleted; ++i)
        {
            if (_states[i] == busy)
            {
                _states[i] = deleted;
                _size--;
                _deleted++;
                return;
            }
        }

    }



    // удаление по позиции
    void erase(size_t pos)
    {
        if (_size == 0) throw std::out_of_range("The vector is empty");
        if (pos + 1 > _size) throw std::out_of_range("Erase position out of range");

        if (pos == 0)
        {
            pop_front();
            return;
        }
        if (pos == _size - 1)
        {
            pop_back();
            return;
        }

        size_t realpos = real_pos(pos);

        _states[realpos] = deleted;
        _size--;
        _deleted++;

        if (need_realocate()) reallocate(_size + DEFAULT_CAPACITY);
    }

    // очищает вектор, помечая все ячейки как empty.
    void clear()
    {
        for (size_t i = 0; i < _capacity; i++)
            _states[i] = empty;

        _size = 0;
        _deleted = 0;
    }


    // резервирование нужного количества памяти
    void reserve(size_t new_capacity)
    {
        if (new_capacity > _capacity) reallocate(new_capacity);
    }

    // подгон размера по _size
    void shrink_to_fit()
    {
        TVector<T> a;
        a.reallocate(_size);
        for (size_t i = 0; i < _size + _deleted - 1; i++)
            if (_states[i] == busy) a.push_back(_data[i]);
        reallocate(_size);
    }

    void resize(size_t new_size, const T& val = T())
    {
        if (new_size == _size) return;
        if (new_size < _size)
            for (size_t i = _capacity, count = 0; i > 0 && count < (_size - new_size); i--)
                if (_states[i] == busy)
                {
                    _states[i] = empty;
                    _size--;
                    count++;
                }
                else
                    for (size_t i = 0; i < _capacity && _size < new_size; i++)
                        if (_states[i] == empty)
                        {
                            _data[i] = val;
                            _states[i] = busy;
                            _size++;
                        }
    }

    // предназначен для безопасного доступа к элементам вектора
    T& at(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        for (size_t i = 0, count = 0; i < _size + _deleted; i++)
            if (_states[i] == busy)
            {
                if (count == index)
                    return _data[i];
                count++;
            }
        throw std::out_of_range("Index out of range"); // на всякий случай
    }
    const T& at(size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        size_t count = 0;
        for (size_t i = 0; i < _size + _deleted; i++)
            if (_states[i] == busy) {
                if (count == index)
                    return _data[i];
                count++;
            }
        throw std::out_of_range("Index out of range");
    }

    // заполняет вектор заданным числом копий одного и того же значения
    void assign(size_t count, const T& val)
    {
        clear();
        reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            _data[i] = val;
            _states[i] = busy;
        }
        _size = count;
    }

    // замена значения по позиции
    void emplace(size_t pos, const T& val)
    {
        if (pos + 1 > _size) throw std::out_of_range("Out of range");

        size_t realpos = real_pos(val);

        _data[realpos] = val;
    }

    // поиск по значению
    friend int find_last(const TVector<T>& vec, const T& val)
    {
        for (size_t i = vec._size - 1 + vec._deleted; i > size_t(-1); i--)
            if (vec[i] == val)
                return i;
        return -1;
    }

    // поиск по условию
    template <typename Predicate>
    friend int find_last(const TVector<T>& vec, Predicate predicate)
    {
        for (int i = vec._size - 1 + vec._deleted; i >= 0; i--)
            if (predicate(vec[i]))
                return i;
        return -1;
    }

    // поиск по значению
    friend TVector<size_t> find_all(const TVector<T>& vec, const T& val)
    {
        TVector<size_t> result;
        for (size_t i = 0; i < vec._size; i++)
            if (vec[i] == val)
                result.push_back(i);
        return result;
    }

    // поиск по условию
    template <typename Predicate>
    friend TVector<size_t> find_all(const TVector<T>& vec, Predicate predicate)
    {
        TVector<size_t> result;
        for (size_t i = 0; i < vec._size; i++)
            if (predicate(vec[i]))
                result.push_back(i);
        return result;
    }

    // алгоритм Фишера-Йейтса
    friend void shuffle(TVector<T>& vec)
    {
        vec.shrink_to_fit();
        std::srand(std::time(NULL));
        for (size_t i = _size - 1; i > 0; i--)
        {
            size_t j = std::rand() % (i + 1);
            T a = vec[i];
            vec[i] = vec[j];
            vec[j] = a;
        }
    }

    // сортироака Хоара
    friend void sort(TVector<T>& vec, int left = 0, int right = -1)
    {
        if (right == -1) right = vec.size() - 1;

        if (left >= right) return;
        T p = vec[(left + right) / 2];
        int i = left, j = right;

        while (i <= j)
        {
            while (vec[i] < p) i++;
            while (vec[j] > p) j--;
            if (i <= j)
            {
                int a = vec[i];
                vec[i] = vec[j];
                vec[j] = a;
                i++;
                j--;
            }
        }

        sort(vec, left, j);
        sort(vec, i, right);
    }
};

