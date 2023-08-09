//
//  stack.hpp
//  datastructures_cpp
//
//  Created by Tom on 07.08.23.
//

#ifndef stack_hpp
#define stack_hpp

#include <memory>

using namespace std;

template <typename T>

class Stack {
  
  class StackNode {
  public:
    T data;
    shared_ptr<StackNode> next;
    StackNode(const T& data) : data(data), next(nullptr) {}
  };
  
  shared_ptr<StackNode> top;
  int size;
public:
  Stack() : top(nullptr), size(0) {}
  
  void push(const T& data) {
    shared_ptr<StackNode> newNode = make_unique<StackNode>(data);
    newNode->next = top;
    top = newNode;
    size++;
  }
  
  T pop() {
    if (top == nullptr)
      throw runtime_error("Stack is empty Exception! Cannot perform pop.");
    shared_ptr<StackNode>node = top;
    top = top->next;
    size--;
    return node->data;
  }
  
  T peek() const {
    if (top == nullptr)
      throw runtime_error("Stack is empty Exception! Cannot perform peek.");
    return top->data;
  }
  
  bool isEmpty() const {
    return size == 0;
  }
  
  int getSize() const{
    return size;
  }
};

#endif /* stack_hpp */
