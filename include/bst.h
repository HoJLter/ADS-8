// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>

template <typename T> class BST {
 private:
  struct Node {
    T data;
    int count;
    Node *left;
    Node *right;
  };

  Node *root;

  Node *addNode(Node *root, T data) {
    if (root == nullptr) {
      root = new Node;
      root->data = data;
      root->count = 1;
      root->left = nullptr;
      root->right = nullptr;
    } else if (data < root->data) {
      root->left = addNode(root->left, data);
    } else if (data > root->data) {
      root->right = addNode(root->right, data);
    } else {
      root->count++;
    }
    return root;
  }

  void delTree(Node *root) {
    if (root == nullptr) {
      return;
    }
    delTree(root->right);
    delTree(root->left);
    delete root;
  }

  Node *delNode(Node *root, T data) {
    if (root == nullptr)
      return root;

    if (data < root->data) {
      root->left = delNode(root->left, data);
    } else if (data > root->data) {
      root->right = delNode(root->right, data);
    } else {
      Node *p = root;
      Node *v;

      if (root->right == nullptr) {
        root = root->left;
      } else if (root->left == nullptr) {
        root = root->right;
      } else {
        v = root->left;

        if (v->right != nullptr) {
          while (v->right->right != nullptr)
            v = v->right;

          root->data = v->right->data;
          root->count = v->right->count;

          p = v->right;
          v->right = v->right->left;
        } else {
          root->data = v->data;
          root->count = v->count;

          p = v;
          root->left = root->left->left;
        }
      }
      delete p;
    }
    return root;
  }

  int depthI(Node *root) {
    if (root == nullptr)
      return -1;

    int left = depthI(root->left);
    int right = depthI(root->right);

    return 1 + (left > right ? left : right);
  }

  int searchI(Node *root, T data) {
    if (root == nullptr) {
      return 0;
    }

    if (root->data == data) {
      return root->count;
    }

    if (data > root->data) {
      return searchI(root->right, data);
    } else {
      return searchI(root->left, data);
    }
  }
  void collectInfoI(Node *root, std::vector<std::pair<T, int>> &out) {
    if (root == nullptr)
      return;

    collectInfoI(root->left, out);
    collectInfoI(root->right, out);

    out.push_back({root->data, root->count});
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { delTree(root); };

  void del(T data) { root = delNode(root, data); }

  void insert(T data) { root = addNode(root, data); }

  int search(T data) { return searchI(root, data); }

  int depth() { return depthI(root); }

  // по тз дерево отсортировано по алфавиту,
  // отсюда такие финты приходится использовать
  void collectInfo(std::vector<std::pair<T, int>> &out) {
    collectInfoI(root, out);
  }
};

#endif // INCLUDE_BST_H_
