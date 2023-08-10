//
//  queue.hpp
//  datastructures_cpp
//
//  Created by Tom on 07.08.23.
//

#ifndef queue_h
#define queue_h

#include <memory>

using namespace std;

template <typename T>

class Queue {

  class QueueNode {
  public:
    T data;
    shared_ptr<QueueNode> prev;
    QueueNode(const T& data) : data(data), prev(nullptr) {}
  };
  
  shared_ptr<QueueNode> head;
  shared_ptr<QueueNode> tail;
  int size;
public:
  Queue() : head(nullptr), tail(nullptr), size(0) {}

  void enqueue(const T& data) {
    shared_ptr<QueueNode> newNode = make_shared<QueueNode>(data);
    if (head == nullptr)
      tail = newNode;
    else
      head->prev = newNode;
    head = newNode;
    size++;
  }

  T dequeue() {
    if (tail == nullptr)
      throw runtime_error("Queue is empty Exception! Cannot perform pop.");
    shared_ptr<QueueNode> node = tail;
    tail = tail->prev;
    size--;
    return node->data;
  }
  
  T peek() const {
    if (tail == nullptr)
      throw runtime_error("Queue is empty Exception! Cannot perform peek.");
    return tail->data;
  }

  bool isEmpty() const {
    return size == 0;
  }
  
  int getSize() const {
    return size;
  }
  
  int getNodeCount() const {
    int count = 0;
    shared_ptr<QueueNode>node = tail;
    while(node != nullptr) {
      count++;
      node = node->prev;
    }
    return count;
  }
};

#endif /* queue_h */
