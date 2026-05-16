// Copyright 2021 NNTU-CS
#include <algorithm>
#include <utility>
#include <vector>
#include <cctype>
#include <fstream>
#include <string>
#include "bst.h"
#include <iostream>

bool isEnglish(char s);
char con_to_low(char s);

void makeTree(BST<std::string>& tree, const char* source) {
    std::ifstream input(source);
    if (!input.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    std::string buffer;
    char cur_char;
    while (input.get(cur_char)) {
        if (isEnglish(cur_char)) {
            buffer.push_back(con_to_low(cur_char));
        }
        else {
            if (!buffer.empty()) {
                tree.insert(buffer);
                buffer.clear();
            }
        }
    }
    if (!buffer.empty()) {
        tree.insert(buffer);
    }
    input.close();
}

bool sort_by_freq(const std::pair<std::string, int>& first,
    const std::pair<std::string, int>& second) {
    return first.second > second.second;
}

void printFreq(BST<std::string>& voc) {
    std::vector<std::pair<std::string, int>> items;
    voc.collectInfo(items);
    std::sort(items.begin(), items.end(), sort_by_freq);
    std::ofstream output("result/freq.txt");
    for (const auto& entry : items) {
        std::cout << entry.first << " - " << entry.second << std::endl;
        if (output.is_open()) {
            output << entry.first << " - " << entry.second << std::endl;
        }
    }
    output.close();
}

bool isEnglish(char s) {
    return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');
}

char con_to_low(char s) {
    if (s >= 'A' && s <= 'Z') {
        return s + ('a' - 'A');
    }
    return s;
}
