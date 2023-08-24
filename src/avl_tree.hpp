//
//  avl_tree.hpp
//  datastructures_cpp
//
//  Created by Tom on 09.08.23.
//

#ifndef avl_tree_hpp
#define avl_tree_hpp

#include <iostream>
#include <memory>

using namespace std;

template <typename T>

class AVLTree {
  
  struct Node {
    T data;
    int height;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Node(const T& data) : data(data), height(1) {}
  };
  
  shared_ptr<Node> root;
  
  int getHeight(const shared_ptr<Node>& node) {
    if (!node)
      return 0;
    return node->height;
  }
  
  int getBalance(const shared_ptr<Node>& node) {
    if (!node)
      return 0;
    return getHeight(node->left) - getHeight(node->right);
  }
  
  shared_ptr<Node> rotateRight(shared_ptr<Node>& y) {
    shared_ptr<Node> x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);
    return x;
  }
  
  shared_ptr<Node> rotateLeft(shared_ptr<Node>& x) {
    shared_ptr<Node> y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
  }
  
  void updateHeight(shared_ptr<Node>& node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  }
  
  shared_ptr<Node> insert(shared_ptr<Node> node, const T& value) {
    if (!node)
      return make_unique<Node>(value);
    
    if (value < node->data)
      node->left = insert(node->left, value);
    else if (value > node->data)
      node->right = insert(node->right, value);
    
    updateHeight(node);
    
    int balance = getBalance(node);
    
    if (balance > 1 && value < node->left->data)
      return rotateRight(node);
    
    if (balance < -1 && value > node->right->data)
      return rotateLeft(node);
    
    if (balance > 1 && value > node->left->data) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    
    if (balance < -1 && value < node->right->data) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    
    return node;
  }
  
  shared_ptr<Node> remove(shared_ptr<Node>& node, const T& value) {
    if (!node)
      return nullptr;
    
    if (value < node->data)
      node->left = remove(node->left, value);
    else if (value > node->data)
      node->right = remove(node->right, value);
    else {
      if (!node->left || !node->right) {
        shared_ptr<Node> temp = node->left ? node->left : node->right;
        node = temp;
      } else {
        shared_ptr<Node> temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
      }
    }
    
    if (!node)
      return nullptr;
    
    updateHeight(node);
    
    int balance = getBalance(node);
    
    if (balance > 1 && getBalance(node->left) >= 0)
      return rotateRight(node);
    
    if (balance > 1 && getBalance(node->left) < 0) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    
    if (balance < -1 && getBalance(node->right) <= 0)
      return rotateLeft(node);
    
    if (balance < -1 && getBalance(node->right) > 0) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    
    return node;
  }
  
  shared_ptr<Node>& minValueNode(shared_ptr<Node>& node) {
    while (node->left)
      node = node->left;
    return node;
  }
  
  int getNodeCount(shared_ptr<Node>& node) {
    if (node == nullptr)
      return 0;
    return 1 + getNodeCount(node->left) + getNodeCount(node->right);
  }

  void traversePreOrder(const shared_ptr<Node>& node, function<void(const T&)> callback) {
    if (node) {
      callback(node->data);
      traversePreOrder(node->left, callback);
      traversePreOrder(node->right, callback);
    }
  }
  
  void traverseInOrder(const shared_ptr<Node>& node, function<void(const T&)> callback) {
    if (node) {
      traverseInOrder(node->left, callback);
      callback(node->data);
      traverseInOrder(node->right, callback);
    }
  }
  
  void traversePostOrder(const shared_ptr<Node>& node, function<void(const T&)> callback) {
    if (node) {
      traversePostOrder(node->left, callback);
      traversePostOrder(node->right, callback);
      callback(node->data);
    }
  }
  
public:
  
  int getNodeCount() {
    return getNodeCount(root);
  }

  void traversePreOrder(function<void(const T&)> callback) {
    traversePreOrder(root, callback);
  }
  
  void traverseInOrder(function<void(const T&)> callback) {
    traverseInOrder(root, callback);
  }
  
  void traversePostOrder(function<void(const T&)> callback) {
    traversePostOrder(root, callback);
  }
  
  void insert(const T& value) {
    root = insert(root, value);
  }
  
  void remove(const T& value) {
    root = remove(root, value);
  }
};

#endif /* avl_tree_hpp */
