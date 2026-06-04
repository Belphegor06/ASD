#pragma once

#include <stdexcept>

template <class T>
struct Node
{
    T value;
    Node<T>* next;

    Node(const T& value, Node<T>* next = nullptr)
        : value(value), next(next)
    {
    }
};

template <class T>
class List
{
private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _size;

public:
    List()
        : _head(nullptr),
        _tail(nullptr),
        _size(0)
    {
    }

    List(const List<T>& other)
        : _head(nullptr),
        _tail(nullptr),
        _size(0)
    {
        Node<T>* cur = other._head;

        while (cur != nullptr)
        {
            push_back(cur->value);
            cur = cur->next;
        }
    }

    ~List()
    {
        clear();
    }

    bool empty() const
    {
        return _head == nullptr;
    }

    size_t size() const
    {
        return _size;
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    Node<T>* front_node()
    {
        return _head;
    }

    const Node<T>* front_node() const
    {
        return _head;
    }

    T& front()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }

        return _head->value;
    }

    const T& front() const
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }

        return _head->value;
    }

    T& back()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }

        return _tail->value;
    }

    const T& back() const
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }

        return _tail->value;
    }

    void push_front(const T& value)
    {
        Node<T>* node = new Node<T>(value);

        if (empty())
        {
            _head = node;
            _tail = node;
            _size++;
            return;
        }

        node->next = _head;
        _head = node;

        _size++;
    }

    void push_back(const T& value)
    {
        Node<T>* node = new Node<T>(value);

        if (empty())
        {
            _head = node;
            _tail = node;
            _size++;
            return;
        }

        _tail->next = node;
        _tail = node;

        _size++;
    }

    void insert(size_t pos, const T& value)
    {
        if (pos == 0)
        {
            push_front(value);
            return;
        }

        Node<T>* cur = _head;
        size_t cur_pos = 0;

        while (cur != nullptr && cur_pos < pos - 1)
        {
            cur = cur->next;
            cur_pos++;
        }

        if (cur == nullptr)
        {
            throw std::out_of_range("Position out of range");
        }

        insert(cur, value);
    }

    void insert(Node<T>* node, const T& value)
    {
        if (node == nullptr || empty())
        {
            throw std::invalid_argument("Invalid node");
        }

        Node<T>* new_node = new Node<T>(value);

        new_node->next = node->next;
        node->next = new_node;

        if (node == _tail)
        {
            _tail = new_node;
        }

        _size++;
    }

    void pop_front()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }

        Node<T>* temp = _head;

        _head = _head->next;

        delete temp;

        if (_head == nullptr)
        {
            _tail = nullptr;
        }

        _size--;
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }

        if (_head == _tail)
        {
            delete _head;

            _head = nullptr;
            _tail = nullptr;

            _size--;

            return;
        }

        Node<T>* cur = _head;

        while (cur->next != _tail)
        {
            cur = cur->next;
        }

        delete _tail;

        cur->next = nullptr;
        _tail = cur;

        _size--;
    }

    void erase(size_t pos)
    {
        if (pos >= _size)
        {
            throw std::out_of_range("Position out of range");
        }

        if (pos == 0)
        {
            pop_front();
            return;
        }

        Node<T>* cur = _head;
        size_t cur_pos = 0;

        while (cur != nullptr && cur_pos < pos - 1)
        {
            cur = cur->next;
            cur_pos++;
        }

        if (cur == nullptr || cur->next == nullptr)
        {
            throw std::out_of_range("Position out of range");
        }

        Node<T>* node_to_delete = cur->next;

        cur->next = node_to_delete->next;

        if (node_to_delete == _tail)
        {
            _tail = cur;
        }

        delete node_to_delete;

        _size--;
    }

    void erase(Node<T>* node)
    {
        if (node == nullptr || empty())
        {
            throw std::invalid_argument("Invalid node");
        }

        if (node == _head)
        {
            pop_front();
            return;
        }

        Node<T>* cur = _head;

        while (cur != nullptr && cur->next != node)
        {
            cur = cur->next;
        }

        if (cur == nullptr)
        {
            throw std::invalid_argument("Node not found in list");
        }

        cur->next = node->next;

        if (node == _tail)
        {
            _tail = cur;
        }

        delete node;

        _size--;
    }
};