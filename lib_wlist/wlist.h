#include <stdexcept>

template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr)
        : value(value), next(next), prev(prev) {
    }
};

template <class T>
class WList {
    Node<T>* _head;
    Node<T>* _tail;

public:
    WList() : _head(nullptr), _tail(nullptr) {}

    //  онструктор копировани€
    WList(const WList<T>& other) : _head(nullptr), _tail(nullptr) {
        Node<T>* cur = other._head;
        while (cur != nullptr) {
            push_back(cur->value);
            cur = cur->next;
        }
    }

    ~WList() {
        while (!is_empty()) {
            pop_front();
        }
    }

    bool is_empty() const { return _head == nullptr; }

    Node<T>* head() const { return _head; }
    Node<T>* tail() const { return _tail; }

    void push_front(const T& value) {
        Node<T>* node = new Node<T>(value, _head, nullptr);
        if (is_empty()) {
            _head = _tail = node;
        }
        else {
            _head->prev = node;
            _head = node;
        }
    }

    void push_back(const T& value) {
        Node<T>* node = new Node<T>(value, nullptr, _tail);
        if (is_empty()) {
            _head = _tail = node;
        }
        else {
            _tail->next = node;
            _tail = node;
        }
    }

    void insert_after(Node<T>* node, const T& value) {
        if (node == nullptr) throw std::invalid_argument("Invalid node");

        Node<T>* new_node = new Node<T>(value, node->next, node);
        if (node->next != nullptr) node->next->prev = new_node;
        else _tail = new_node;
        node->next = new_node;
    }

    void insert_before(Node<T>* node, const T& value) {
        if (node == nullptr) throw std::invalid_argument("Invalid node");

        Node<T>* new_node = new Node<T>(value, node, node->prev);
        if (node->prev != nullptr) node->prev->next = new_node;
        else _head = new_node;
        node->prev = new_node;
    }

    void erase(Node<T>* node) {
        if (node == nullptr) throw std::invalid_argument("Invalid node");

        if (node->prev != nullptr) node->prev->next = node->next;
        else _head = node->next;

        if (node->next != nullptr) node->next->prev = node->prev;
        else _tail = node->prev;

        node->next = node->prev = nullptr; // обезопасим старый узел
        delete node;
    }

    void pop_front() {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node<T>* temp = _head;
        _head = _head->next;
        if (_head != nullptr) _head->prev = nullptr;
        else _tail = nullptr;
        temp->next = temp->prev = nullptr;
        delete temp;
    }

    void pop_back() {
        if (is_empty()) throw std::runtime_error("List is empty");
        Node<T>* temp = _tail;
        _tail = _tail->prev;
        if (_tail != nullptr) _tail->next = nullptr;
        else _head = nullptr;
        temp->next = temp->prev = nullptr;
        delete temp;
    }
};
