//
//  heap.hpp
//  datastructures_cpp
//
//  Created by Tom on 28.08.23.
//

#ifndef heap_hpp
#define heap_hpp

#include <iostream>
#include <memory>

using namespace std;

template <typename T, typename Comparator>

struct HeapNode {
  T data;
  std::shared_ptr<HeapNode<T, Comparator>> left;
  std::shared_ptr<HeapNode<T, Comparator>> right;
  HeapNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T, typename Comparator>

class Heap {
private:
  std::shared_ptr<HeapNode<T, Comparator>> root;
  int size;
  
public:
  Heap() : root(nullptr), size(0) {}
  
  void insert(T val) {
    std::shared_ptr<HeapNode<T, Comparator>> newHeapNode = std::make_shared<HeapNode<T, Comparator>>(val);
    root = merge(root, newHeapNode);
    size++;
  }
  
  T pop() {
    if (root == nullptr)
      throw runtime_error("Heap is empty Exception! Cannot perform pop.");
    T value = root->data;
    root = merge(root->left, root->right);
    size--;
    return value;
  }
  
  T peek() {
    if (root == nullptr)
      throw runtime_error("Heap is empty Exception! Cannot perform peek.");
    return root->data;
  }
  
  bool isEmpty() {
    return root == nullptr;
  }
  
  int getSize() {
    return size;
  }
  
private:
  std::shared_ptr<HeapNode<T, Comparator>> merge(std::shared_ptr<HeapNode<T, Comparator>> a, std::shared_ptr<HeapNode<T, Comparator>> b) {
    if (!a) return b;
    if (!b) return a;
    if (Comparator()(a, b))
      std::swap(a, b);
    a->right = merge(a->right, b);
    std::swap(a->left, a->right);
    return a;
  }
};

struct MaximumComparator {
  template <typename T>
  bool operator()(const std::shared_ptr<HeapNode<T, MaximumComparator>>& a, const std::shared_ptr<HeapNode<T, MaximumComparator>>& b) {
    return a->data < b->data;
  }
};

struct MinimumComparator {
  template <typename T>
  bool operator()(const std::shared_ptr<HeapNode<T, MinimumComparator>>& a, const std::shared_ptr<HeapNode<T, MinimumComparator>>& b) {
    return a->data > b->data;
  }
};

#endif /* heap_hpp */
