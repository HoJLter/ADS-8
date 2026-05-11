// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <utility>
#include <string>
#include <vector>
#include "bst.h"

bool isLetter(char ch) {
  return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122);
}

char toLowercase(char ch) {
  if (ch >= 65 && ch <= 90) {
    return ch + 32;
  }
  return ch;
}

void makeTree(BST<std::string> &tree, const char *filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  char ch;
  std::string word;

  while ((ch = file.get()) != EOF) {
    ch = toLowercase(ch);

    if (isLetter(ch)) {
      word.push_back(ch);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word = "";
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

bool compare(const std::pair<std::string, int> &a,
             const std::pair<std::string, int> &b) {
  return a.second > b.second;
}

void printFreq(BST<std::string> &tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.collectInfo(words);

  std::sort(words.begin(), words.end(), compare);

  std::ofstream out("result/freq.txt");

  for (const auto &word : words) {
    std::cout << word.first << " : " << word.second << '\n';

    if (out) {
      out << word.first << " : " << word.second << '\n';
    }
  }

  out.close();
}
