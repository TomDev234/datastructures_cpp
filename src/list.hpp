//
//  list.hpp
//  datastructures_cpp
//
//  Created by Tom on 07.08.23.
//

#ifndef list_h
#define list_h

#include <memory>
#include <functional>

using namespace std;

template <typename T>

class List {
  struct ListNode {
    T data;
    shared_ptr<ListNode>next;
    shared_ptr<ListNode>prev;
    ListNode() : data(T()), next(nullptr), prev(nullptr) {}
    ListNode(const T& data) : data(data), next(nullptr), prev(nullptr) {}
  };
  
  shared_ptr<ListNode>headGuard;
  shared_ptr<ListNode>tailGuard;
  int size;
public:
  List() {
    headGuard = make_shared<ListNode>();
    tailGuard = make_shared<ListNode>();
    headGuard->next = tailGuard;
    tailGuard->prev = headGuard;
    size = 0;
  }
  
  void addHead(const T& data) {
    shared_ptr<ListNode>node = make_shared<ListNode>(data);
    node->next = headGuard->next;
    node->prev = headGuard;
    headGuard->next->prev = node;
    headGuard->next = node;
    size++;
  }
  
  void addTail(const T& data) {
    shared_ptr<ListNode>node = make_shared<ListNode>(data);
    node->prev = tailGuard->prev;
    node->next = tailGuard;
    tailGuard->prev->next = node;
    tailGuard->prev = node;
    size++;
  }
  
  void addData(T data) {
    shared_ptr<ListNode>listNode = headGuard->next;
    while(listNode != tailGuard && listNode->data < data)
      listNode = listNode->next;
    if(listNode != tailGuard) {
      shared_ptr<ListNode>newNode = make_shared<ListNode>;
      newNode->data = data;
      newNode->next = listNode;
      newNode->prev = listNode->prev;
      listNode->prev->next = newNode;
      listNode->prev = newNode;
    }
  }
  
  T removeHead() {
    if(isEmpty())
      throw runtime_error("List is empty Exception! Cannot perform removeHead.");
    shared_ptr<ListNode>listNode = headGuard->next;
    headGuard->next->next->prev = headGuard;
    headGuard->next = headGuard->next->next;
    size--;
    return listNode->data;
  }
  
  T removeTail() {
    if(isEmpty())
      throw runtime_error("List is empty Exception! Cannot perform removeTail.");
    shared_ptr<ListNode>listNode = tailGuard->prev;
    tailGuard->prev->prev->next = tailGuard;
    tailGuard->prev = tailGuard->prev->prev;
    size--;
    return listNode->data;
  }
  
  void removeData(T data) {
    if(isEmpty())
      throw runtime_error("List is empty Exception! Cannot perform removeData.");
    shared_ptr<ListNode>listNode = headGuard->next;
    while(listNode != tailGuard && listNode.data != data)
      listNode = listNode->next;
    if(listNode != tailGuard) {
      listNode->next->prev = listNode->prev;
      listNode->prev->next = listNode->next;
    }
  }
  
  int getSize() {
    return size;
  }
  
  int getNodeCount() {
    int count = 0;
    shared_ptr<ListNode>node = headGuard->next;
    while(node != tailGuard) {
      count++;
      node = node->next;
    }
    return count;
  }
  
  bool isEmpty() {
    return size == 0;
  }
  
  void reverse() {
    if (isEmpty())
      throw runtime_error("List is empty Exception! Cannot perform reverse.");
    shared_ptr<ListNode>current = headGuard->next;
    while (current != tailGuard) {
      swap(current->prev, current->next);
      current = current->prev; // Move to the next node (which is the previous node after swapping)
    }
    swap(headGuard->next, tailGuard->prev); // Update headGuard and tailGuard pointers after reversing
    headGuard->next->prev = headGuard; // Update the prev pointer of the new head node
    tailGuard->prev->next = tailGuard; // Update the next pointer of the new tail node
  }
  
  void traverse(const function<void(T& data)>callback) {
    shared_ptr<ListNode>listNode = headGuard->next;
    while(listNode != tailGuard) {
      callback(listNode->data);
      listNode = listNode->next;
    }
  }
  
  // --- Merge Sort

  shared_ptr<ListNode>findMiddle() {
    shared_ptr<ListNode> slow = headGuard;
    shared_ptr<ListNode> fast = headGuard;
    while (fast != tailGuard && fast->next != tailGuard) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }

  void merge(List& left, List& right) {
    shared_ptr<ListNode>leftCurrent = left.headGuard->next;
    shared_ptr<ListNode>rightCurrent = right.headGuard->next;
    shared_ptr<ListNode>mergeCurrent = headGuard;

    while (leftCurrent != left.tailGuard && rightCurrent != right.tailGuard) {
      if (*leftCurrent->data <= *rightCurrent->data) {
        mergeCurrent->next = leftCurrent;
        leftCurrent->prev = mergeCurrent;
        leftCurrent = leftCurrent->next;
      }
      else {
        mergeCurrent->next = rightCurrent;
        rightCurrent->prev = mergeCurrent;
        rightCurrent = rightCurrent->next;
      }
      mergeCurrent = mergeCurrent->next;
    }

    while (leftCurrent != left.tailGuard) {
      mergeCurrent->next = leftCurrent;
      leftCurrent->prev = mergeCurrent;
      leftCurrent = leftCurrent->next;
      mergeCurrent = mergeCurrent->next;
    }

    while (rightCurrent != right.tailGuard) {
      mergeCurrent->next = rightCurrent;
      rightCurrent->prev = mergeCurrent;
      rightCurrent = rightCurrent->next;
      mergeCurrent = mergeCurrent->next;
    }

    mergeCurrent->next = tailGuard;
    tailGuard->prev = mergeCurrent;
  }

  void mergeSort() {
    if (headGuard->next == tailGuard || headGuard->next->next == tailGuard) {
      return;
    }

    List leftHalf;
    List rightHalf;

    shared_ptr<ListNode> middle = findMiddle();

    // Copy data from original list to leftHalf
    shared_ptr<ListNode> current = headGuard->next;
    while (current != middle->next) {
      leftHalf.addTail(current->data);
      current = current->next;
    }

    // Copy data from original list to rightHalf
    while (current != tailGuard) {
      rightHalf.addTail(current->data);
      current = current->next;
    }

    leftHalf.mergeSort();
    rightHalf.mergeSort();
    merge(leftHalf, rightHalf);
  }
  
  // ---
  
  bool isSorted() {
    shared_ptr<ListNode>head = headGuard->next;
    if (head == tailGuard || head->next == tailGuard) {
      // If the list is empty or has only one element, it's considered sorted
      return true;
    }
    shared_ptr<ListNode>current = head;
    while (current->next != tailGuard) {
      if (*current->data > *current->next->data) {
        // If a value is greater than its next value, the list is not sorted
        return false;
      }
      current = current->next;
    }
    return true;
  }
  
  class Iterator {
  private:
    shared_ptr<ListNode> current;
    
  public:
    Iterator(shared_ptr<ListNode> node) : current(node) {}
    
    T operator*() {
      return current->data;
    }
    
    Iterator& operator++() {
      if (current) {
        current = current->next;
      }
      return *this;
    }
    
    bool operator!=(const Iterator& other) {
      return current != other.current;
    }
  };
  
  Iterator begin() {
    return Iterator(headGuard->next);
  }
  
  Iterator end() {
    return Iterator(tailGuard);
  }
  
  class ReverseIterator {
  private:
    shared_ptr<ListNode> current;
    
  public:
    ReverseIterator(shared_ptr<ListNode> node) : current(node) {}
    
    T operator*() {
      return current->data;
    }
    
    ReverseIterator& operator--() {
      if (current) {
        current = current->prev;
      }
      return *this;
    }
    
    bool operator!=(const ReverseIterator& other) {
      return current != other.current;
    }
  };
  
  ReverseIterator rbegin() {
    return ReverseIterator(tailGuard->prev);
  }
  
  ReverseIterator rend() {
    return ReverseIterator(headGuard);
  }
};

#endif /* list_h */
