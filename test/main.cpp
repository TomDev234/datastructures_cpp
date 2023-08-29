//
//  main.cpp
//  datastructures_tests
//
//  Created by Tom on 07.08.23.
//

#include "datastructures.hpp"
#include <iostream>

using namespace std;

class NumberNode {
public:
  virtual ~NumberNode() = default;
  virtual string toString() const = 0;
  // Virtual function for the << operator
  virtual ostream& print(ostream& stream) const {
    stream << "NumberNode";
    return stream;
  }
  // Friend function to use the virtual function
  friend ostream& operator << (ostream& stream, const NumberNode& node) {
    return node.print(stream);
  }
  virtual bool greaterThan(const NumberNode& node) const = 0;
};

class IntNode : public NumberNode {
public:
  int i;
  IntNode() : i(0) {}
  IntNode(int i) : i(i) {}
  string toString() const override {
    return to_string(i);
  }
  // Override the virtual function
  ostream& print(ostream& stream) const override {
    stream << toString();
    return stream;
  }
  bool greaterThan(const NumberNode& other) const override {
    bool result;
    const IntNode* otherInt = dynamic_cast<const IntNode*>(&other);
    if (otherInt != nullptr)
      result = i > otherInt->i;
    else
      result = false;
    return result;
  }
};

class FloatNode : public NumberNode {
public:
  float f;
  FloatNode() : f(0) {}
  FloatNode(float f) : f(f) {}
  string toString() const override {
    return to_string(f);
  }
  // Override the virtual function
  ostream& print(ostream& stream) const override {
    stream << toString();
    return stream;
  }
  bool greaterThan(const NumberNode& other) const override {
    bool result;
    const FloatNode* otherFloat = dynamic_cast<const FloatNode*>(&other);
    if(otherFloat != nullptr)
      result = f > otherFloat->f;
    else
      result = false;
    return result;
  }
};

int testStack () {
  cout << "Stack Test\n";
  cout << "----------\n";

  const int numberOfNodes = 10;
  int result = 0;
  Stack<shared_ptr<NumberNode>> stack;

  for (int i = 0; i < numberOfNodes; i++) {
    if(i == numberOfNodes / 2) {
      shared_ptr<FloatNode>node = make_shared<FloatNode>(20.2f);
      stack.push(node);
    }
    else {
      shared_ptr<IntNode>node = make_shared<IntNode>(i);
      stack.push(node);
    }
  }

  cout << "Stack Size = " << stack.getSize() << endl;
  if (stack.getNodeCount() != numberOfNodes) {
    cout << "Wrong Node Count Error!\n";
    result = 1;
  }

  cout << "Popped Elements:";
  while (!stack.isEmpty()) {
    shared_ptr<NumberNode>node = stack.pop();
    cout << *node << " ";
  }
  cout << endl << endl;
  
  return result;
}

int testQueue() {
  cout << "Queue Test\n";
  cout << "----------\n";
  
  int result = 0;
  
  Queue<shared_ptr<NumberNode>> queue;
  queue.enqueue(make_shared<IntNode>(1));
  queue.enqueue(make_shared<IntNode>(2));
  queue.enqueue(make_shared<IntNode>(3));
  queue.enqueue(make_unique<FloatNode>(10.1f));
  queue.enqueue(make_unique<FloatNode>(20.2f));
  queue.enqueue(make_shared<FloatNode>(30.3f));
  
  if (queue.getNodeCount() != 6) {
    cout << "Wrong Node Count Error!\n";
    result = 1;
  }
  
  cout << "Queue Size=" << queue.getSize() << endl;
  cout << "Head Element:" << queue.peek()->toString() << endl;
  
  while (!queue.isEmpty()) {
    shared_ptr<NumberNode>node = queue.dequeue();
    cout << *node << " ";
  }
  cout << endl << endl;
  
  return result;
}

int testList() {
  cout << "List Test\n";
  cout << "---------\n";

  int result = 0;
  
  List<shared_ptr<NumberNode>> list;
  
  list.addHead(make_shared<IntNode>(1));
  list.addHead(make_shared<IntNode>(2));
  list.addHead(make_shared<IntNode>(3));
  list.addHead(make_shared<IntNode>(4));
  list.addHead(make_shared<IntNode>(5));
  list.addTail(make_shared<IntNode>(20));
  list.addTail(make_shared<IntNode>(21));
  list.addTail(make_shared<FloatNode>(22.2f));
  list.addTail(make_shared<IntNode>(26));
  list.addTail(make_shared<IntNode>(23));
  list.addTail(make_shared<IntNode>(25));
  list.addTail(make_shared<IntNode>(24));

  if (list.getNodeCount() != 12) {
    cout << "Wrong Node Count Error!\n";
    result = 1;
  }
  
  cout << "List Size=" << list.getSize() << endl;
  
  cout << "List Elements:";
  list.traverse([](shared_ptr<NumberNode> data) {
    cout << data->toString() << " ";
  });
  cout << endl;

  shared_ptr<NumberNode>node = list.removeHead();
  cout << "Remove Head:" << node->toString() << " ";

  node = list.removeTail();
  cout << "Remove Tail:" << node->toString() << endl;

  if(list.getNodeCount() != 10) {
    cout << "Wrong Node Count Error!\n";
    result = 1;
  }
  
  cout << "Forward Iteration:";
  for (auto it = list.begin(); it != list.end(); ++it) {
    cout << **it << " ";
  }
  cout << endl;

  cout << "Backward Iteration:";
  for (auto rit = list.rbegin(); rit != list.rend(); --rit) {
    cout << **rit << " ";
  }
  cout << endl;

  cout << "List reversed: ";
  list.reverse();
  list.traverse([](shared_ptr<NumberNode>node) {
    cout << *node << " ";
  });
  cout << endl;
  
  list.mergeSort();
  
  cout << "Sorted List: ";
  list.traverse([](shared_ptr<NumberNode> data) {
    cout << data->toString() << " ";
  });
  cout << endl;
  
  cout << "List Merge Sort does not work correctly!" << endl;

  if (!list.isSorted()) {
    cout << "List not sorted Error!\n";
    result = 1;
  }
  else
    cout << "List is sorted.\n";
  
  cout << endl;
  
  return result;
}

int testHeap() {
  cout << "Heap Test\n";
  cout << "---------\n";

  Heap<int, MaximumComparator> maximumHeap;
  Heap<int, MinimumComparator> minimumHeap;
  
  int result = 0;
  array<int,5>randomData = {3,1,4,2,5};
  array<int,5>maximumData = {5,4,3,2,1};
  array<int,5>minimumData = {1,2,3,4,5};
  
  for (int i = 0; i < randomData.size(); i++)
    maximumHeap.insert(randomData[i]);
  
  for (int i = 0; i < randomData.size(); i++)
    minimumHeap.insert(randomData[i]);
  
  std::cout << "Maximum Heap Elements: ";
  int count = 0;
  while (!maximumHeap.isEmpty()) {
    int value = maximumHeap.pop();
    if (value != maximumData.at(count)) {
      result = 1;
      break;
    }
    count++;
    std::cout << value << " ";
  }
  std::cout << std::endl;
  
  std::cout << "Minimum Heap Elements: ";
  count = 0;
  while (!minimumHeap.isEmpty()) {
    int value = minimumHeap.pop();
    if (value != minimumData.at(count)) {
      result = 1;
      break;
    }
    count++;
    std::cout << value << " ";
  }
  
  if (result == 0)
    std::cout << std::endl << endl;
  else
    cout << "\nHeap Test failed!\n\n";
  
  return result;
}

int testAVLTree() {
  cout << "Test AVLTree\n";
  cout << "------------\n";
  
  int result = 0;
  AVLTree<int> tree;
  
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);
  tree.insert(25);
  
  int nodeCount = tree.getNodeCount();
  if (nodeCount != 6) {
    cout << "Wrong Number of Nodes Error!\n";
    result = 1;
  }
    
  cout << "Preorder traversal : ";
  tree.traversePreOrder([](const int& value) {
    cout << value << " ";
  });
  cout << endl;
  
  cout << "Inorder traversal  : ";
  tree.traverseInOrder([](const int& value) {
    cout << value << " ";
  });
  cout << endl;

  cout << "Postorder traversal: ";
  tree.traversePostOrder([](const int& value) {
    cout << value << " ";
  });
  cout << endl;
  
  tree.remove(30);
  tree.remove(40);
  
  nodeCount = tree.getNodeCount();
  if (nodeCount != 4) {
    cout << "Wrong Number of Nodes Error!\n";
    result = 1;
  }
  
  cout << endl;
  
  return result;
}

int main() {
  int result = 0;
  result += testStack();
  result += testQueue();
  result += testList();
  result += testHeap();
  result += testAVLTree();
  cout << "Failed Tests " << result << endl;
  return result;
}
