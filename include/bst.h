// Copyright 2026 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>

template<typename T>
class BST {
private:
    struct Node {
        T info;
        int count;
        Node* left;
        Node* right;
    };
    Node* top;

    Node* createNode(const T& value) {
        Node* newNode = new Node;
        newNode->info = value;
        newNode->count = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    Node* connect(Node* current, const T& value) {
        if (current == nullptr) {
            return createNode(value);
        }
        if (value < current->info) {
            current->left = connect(current->left, value);
        }
        else if (value > current->info) {
            current->right = connect(current->right, value);
        }
        else {
            current->count++;
        }
        return current;
    }

    void collectData(Node* current,
        std::vector<std::pair<T, int>>& buffer) {
        if (current == nullptr) {
            return;
        }
        collectData(current->left, buffer);
        buffer.push_back({ current->info, current->count });
        collectData(current->right, buffer);
    }

    void deleteAll(Node* current) {
        if (current == nullptr) {
            return;
        }
        deleteAll(current->left);
        deleteAll(current->right);
        delete current;
    }

    int findCount(Node* current, const T& value) const {
        if (current == nullptr) {
            return 0;
        }
        if (current->info == value) {
            return current->count;
        }
        if (value < current->info) {
            return findCount(current->left, value);
        }
        else {
            return findCount(current->right, value);
        }
    }

    int computeHeight(Node* current) const {
        if (current == nullptr) {
            return -1;
        }
        int leftHeight = computeHeight(current->left);
        int rightHeight = computeHeight(current->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

public:
    BST() : top(nullptr) {}

    ~BST() {
        deleteAll(top);
    }

    void insert(const T& value) {
        top = connect(top, value);
    }

    int depth() const {
        return computeHeight(top);
    }

    int search(const T& value) const {
        return findCount(top, value);
    }

    void collectInfo(std::vector<std::pair<T, int>>& output) {
        collectData(top, output);
    }
};

#endif  // INCLUDE_BST_H_
