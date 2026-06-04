#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>

template<class T>
class BinaryTree
{
private:

    struct Node
    {
        T data;

        Node* left;
        Node* right;

        Node(const T& value)
            : data(value),
            left(nullptr),
            right(nullptr)
        {
        }
    };

    Node* root;
    size_t _size;

private:

    // Очистка дерева
    void clear(Node* node)
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

    // Поиск узла
    Node* findNode(const T& value) const
    {
        Node* current = root;

        while (current != nullptr)
        {
            if (value < current->data)
            {
                current = current->left;
            }
            else if (value > current->data)
            {
                current = current->right;
            }
            else
            {
                return current;
            }
        }

        return nullptr;
    }

    // Максимум поддерева
    Node* findMax(Node* node) const
    {
        while (node->right != nullptr)
        {
            node = node->right;
        }

        return node;
    }

    // Рекурсивное удаление
    Node* erase(Node* node, const T& value)
    {
        if (node == nullptr)
            throw std::runtime_error("Element not found");

        if (value < node->data)
        {
            node->left = erase(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = erase(node->right, value);
        }
        else
        {
            // Случай 1: лист
            if (node->left == nullptr &&
                node->right == nullptr)
            {
                delete node;
                _size--;

                return nullptr;
            }

            // Случай 2: только правый потомок
            if (node->left == nullptr)
            {
                Node* temp = node->right;

                delete node;
                _size--;

                return temp;
            }

            // Случай 3: только левый потомок
            if (node->right == nullptr)
            {
                Node* temp = node->left;

                delete node;
                _size--;

                return temp;
            }

            // Случай 4: два потомка
            Node* maxLeft = findMax(node->left);

            node->data = maxLeft->data;

            node->left = erase(node->left, maxLeft->data);
        }

        return node;
    }

    // Прямой обход
    void preorder(Node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->data << " ";

        preorder(node->left);
        preorder(node->right);
    }

    // Симметричный обход
    void inorder(Node* node) const
    {
        if (node == nullptr)
            return;

        inorder(node->left);

        std::cout << node->data << " ";

        inorder(node->right);
    }

    // Обратный обход
    void postorder(Node* node) const
    {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);

        std::cout << node->data << " ";
    }

    // Красивый вывод дерева
    void printTree(Node* node, int space) const
    {
        if (node == nullptr)
            return;

        space += 5;

        printTree(node->right, space);

        std::cout << '\n';

        for (int i = 5; i < space; i++)
        {
            std::cout << ' ';
        }

        std::cout << node->data;

        printTree(node->left, space);
    }

public:

    BinaryTree()
    {
        root = nullptr;
        _size = 0;
    }

    ~BinaryTree()
    {
        clear();
    }

    void insert(const T& value)
    {
        if (contains(value))
            throw std::runtime_error("Element already exists");

        Node* newNode = new Node(value);

        if (root == nullptr)
        {
            root = newNode;
            _size++;

            return;
        }

        Node* current = root;

        while (true)
        {
            if (value < current->data)
            {
                if (current->left == nullptr)
                {
                    current->left = newNode;
                    break;
                }

                current = current->left;
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = newNode;
                    break;
                }

                current = current->right;
            }
        }

        _size++;
    }

    bool contains(const T& value) const
    {
        return findNode(value) != nullptr;
    }

    T& find(const T& value)
    {
        Node* node = findNode(value);

        if (node == nullptr)
            throw std::runtime_error("Element not found");

        return node->data;
    }

    void erase(const T& value)
    {
        if (root == nullptr)
            throw std::runtime_error("Tree is empty");

        root = erase(root, value);
    }

    size_t size() const
    {
        return _size;
    }

    bool empty() const
    {
        return _size == 0;
    }

    void clear()
    {
        clear(root);

        root = nullptr;
        _size = 0;
    }

    void print_preorder() const
    {
        preorder(root);
        std::cout << '\n';
    }

    void print_inorder() const
    {
        inorder(root);
        std::cout << '\n';
    }

    void print_postorder() const
    {
        postorder(root);
        std::cout << '\n';
    }

    void print_bfs() const
    {
        if (root == nullptr)
        {
            std::cout << '\n';
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();

            std::cout << current->data << " ";

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }

        std::cout << '\n';
    }

    void print_tree() const
    {
        printTree(root, 0);
        std::cout << '\n';
    }
};