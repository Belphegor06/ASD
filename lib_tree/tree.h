#pragma once

#include <iostream>
#include <queue>
#include <stdexcept>

template <class T>
class Tree
{
private:

    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value), left(nullptr), right(nullptr)
        {
        }
    };

    Node* root;

private:

    // удалаяем рекурсией
    void clear(Node* node)
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

    // прямой обход (центр - лево - право)
    void preorder(Node* node) const
    {
        if (node == nullptr)
            return;

        std::cout << node->data << " ";

        preorder(node->left);
        preorder(node->right);
    }

    // симметричный обход (лево - центр - право)
    void inorder(Node* node) const
    {
        if (node == nullptr)
            return;

        inorder(node->left);

        std::cout << node->data << " ";

        inorder(node->right);
    }

    // обратный обход (лево - правое - центр)
    void postorder(Node* node) const
    {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);

        std::cout << node->data << " ";
    }

    // вывод дерева боком
    void printTree(Node* node, int space) const
    {
        if (node == nullptr)
            return;

        space += 5;

        printTree(node->right, space);

        std::cout << '\n';

        for (int i = 5; i < space; i++)
            std::cout << ' ';

        std::cout << node->data;

        printTree(node->left, space);
    }

public:

    Tree()
    {
        root = nullptr;
    }

    ~Tree()
    {
        clear(root);
    }

    bool empty() const
    {
        return root == nullptr;
    }

    void insert(const T& value)
    {
        Node* newNode = new Node(value);

        if (root == nullptr)
        {
            root = newNode;
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
                return;
            }

            if (current->right == nullptr)
            {
                current->right = newNode;
                return;
            }

            q.push(current->left);
            q.push(current->right);
        }
    }

    bool find(const T& value) const
    {
        if (root == nullptr)
            return false;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();

            if (current->data == value)
                return true;

            if (current->left)
                q.push(current->left);

            if (current->right)
                q.push(current->right);
        }

        return false;
    }

    // удаление 1 элемента
    void erase(const T& value)
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

            if (last->data == value)
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
            throw std::runtime_error("Element not found");

        // в дереве только корень
        if (last == root &&
            root->left == nullptr &&
            root->right == nullptr)
        {
            delete root;
            root = nullptr;
            return;
        }

        target->data = last->data;

        if (parentLast->right == last)
            parentLast->right = nullptr;
        else
            parentLast->left = nullptr;

        delete last;
    }

    // прямой обход
    void print_preorder() const
    {
        preorder(root);
        std::cout << '\n';
    }

    // симметричный обход
    void print_inorder() const
    {
        inorder(root);
        std::cout << '\n';
    }

    // обратный обход
    void print_postorder() const
    {
        postorder(root);
        std::cout << '\n';
    }

    // обход в ширину
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

    // вывод дерева
    void print_tree() const
    {
        printTree(root, 0);
        std::cout << '\n';
    }
};