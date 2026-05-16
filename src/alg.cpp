// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

namespace {

    bool isEnglish(char ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }

    char toLower(char ch) {
        if (ch >= 'A' && ch <= 'Z') return ch + ('a' - 'A');
        return ch;
    }

}  // namespace

void makeTree(BST<std::string>& tree, const char* source) {
    std::ifstream input(source);
    if (!input.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    std::string buffer;
    char curChar;
    while (input.get(curChar)) {
        if (isEnglish(curChar)) {
            buffer.push_back(toLower(curChar));
        }
        else {
            if (!buffer.empty()) {
                tree.insert(buffer);
                buffer.clear();
            }
        }
    }
    if (!buffer.empty()) tree.insert(buffer);
    input.close();
}

bool compareByFreq(const std::pair<std::string, int>& first,
    const std::pair<std::string, int>& second) {
    return first.second > second.second;
}

void printFreq(BST<std::string>& voc) {
    std::vector<std::pair<std::string, int>> items;
    voc.collectInfo(items);
    std::sort(items.begin(), items.end(), compareByFreq);

    std::ofstream output("result/freq.txt");
    for (const auto& entry : items) {
        std::cout << entry.first << " - " << entry.second << std::endl;
        if (output.is_open()) output << entry.first << " - " << entry.second << std::endl;
    }
    output.close();
}
