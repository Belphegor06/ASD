#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>

#include "../lib_itable/itable.h"

template<class TKey, class TVal>
class TableOnTree : public Table<TKey, TVal>
{
private:

    using Row = typename Table<TKey, TVal>::Row;

    struct Node
    {
        Row data;

        Node* left;
        Node* right;

        Node(const TKey& key, const TVal& value)
        {
            data.key = key;
            data.value = value;

            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;
    size_t _size;

private:

    void clear(Node* node)
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

    Node* findNode(const TKey& key) const
    {
        if (root == nullptr)
            return nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();

            if (current->data.key == key)
                return current;

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }

        return nullptr;
    }

public:

    TableOnTree()
    {
        root = nullptr;
        _size = 0;
    }

    ~TableOnTree()
    {
        clear(root);
    }

    void insert(const TKey& key, const TVal& value) override
    {
        if (contains(key))
            throw std::runtime_error("Key already exists");

        Node* newNode = new Node(key, value);

        if (root == nullptr)
        {
            root = newNode;
            _size++;
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();

            if (current->left == nullptr)
            {
                current->left = newNode;
                _size++;
                return;
            }

            if (current->right == nullptr)
            {
                current->right = newNode;
                _size++;
                return;
            }

            q.push(current->left);
            q.push(current->right);
        }
    }

    void erase(const TKey& key) override
    {
        if (root == nullptr)
            throw std::runtime_error("Tree is empty");

        Node* target = nullptr;
        Node* last = nullptr;
        Node* parentLast = nullptr;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            last = q.front();
            q.pop();

            if (last->data.key == key)
                target = last;

            if (last->left)
            {
                parentLast = last;
                q.push(last->left);
            }

            if (last->right)
            {
                parentLast = last;
                q.push(last->right);
            }
        }

        if (target == nullptr)
            throw std::runtime_error("Key not found");

        if (last == root &&
            root->left == nullptr &&
            root->right == nullptr)
        {
            delete root;
            root = nullptr;
            _size--;
            return;
        }

        target->data = last->data;

        if (parentLast->right == last)
            parentLast->right = nullptr;
        else
            parentLast->left = nullptr;

        delete last;

        _size--;
    }

    TVal& find(const TKey& key) override
    {
        Node* node = findNode(key);

        if (node == nullptr)
            throw std::runtime_error("Key not found");

        return node->data.value;
    }

    bool contains(const TKey& key) const override
    {
        return findNode(key) != nullptr;
    }

    size_t size() const override
    {
        return _size;
    }

    bool empty() const override
    {
        return _size == 0;
    }

    void clear() override
    {
        clear(root);

        root = nullptr;
        _size = 0;
    }

    void print() const override
    {
        if (root == nullptr)
        {
            std::cout << "Table is empty\n";
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();

            std::cout
                << current->data.key
                << " : "
                << current->data.value
                << '\n';

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }
    }
};