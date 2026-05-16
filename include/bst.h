// Copyright 2026 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <utility>
#include <vector>
#include <string>

template <typename T> class BST {
private:
    struct Node {
        T info;
        int count;
        Node* left;
        Node* right;
    };
    Node* top;
    Node* connect(Node* current, T value) {
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
    Node* createNode(T value) {
        Node* newNode = new Node;
        newNode->info = value;
        newNode->count = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    void Data(Node* current, std::vector<std::pair<T, int>>& buffer) {
        if (current == nullptr) return;
        Data(current->left, buffer);
        buffer.push_back({ current->info, current->count });
        Data(current->right, buffer);
    }
    void Erase_all(Node* current) {
        if (current == nullptr) return;
        Erase_all(current->left);
        Erase_all(current->right);
        delete current;
    }
    int findCount(Node* current, T value) {
        if (current == nullptr) return 0;
        if (current->info == value) return current->count;
        if (value < current->info) {
            return findCount(current->left, value);
        }
        else {
            return findCount(current->right, value);
        }
    }
    int com_height(Node* current) {
        if (current == nullptr) return -1;
        int leftHeight = com_height(current->left);
        int rightHeight = com_height(current->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
    
public:
    BST() : top(nullptr) {}
    ~BST() { Erase_all(top); }
    void insert(T value) { top = connect(top, value); }
    int depth() { return com_height(top); }
    int search(T value) { return findCount(top, value); }
    void collectInfo(std::vector<std::pair<T, int>>& output) {
        Data(top, output);
    }
};

#endif  // INCLUDE_BST_H_
