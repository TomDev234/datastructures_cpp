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
  list.addTail(make_shared<IntNode>(23));
  list.addTail(make_shared<IntNode>(24));
  list.addTail(make_shared<IntNode>(25));
  list.addTail(make_shared<IntNode>(26));
  
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
  
  cout << "Forward Iteration:\n";
  for (auto it = list.begin(); it != list.end(); ++it) {
    cout << **it << " ";
  }
  cout << endl;

  cout << "Backward Iteration:\n";
  for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
    cout << **rit << " ";
  }
  cout << endl;

  cout << "List reversed: ";
  list.reverse();
  list.traverse([](shared_ptr<NumberNode>node) {
    cout << *node << " ";
  });
  cout << endl << endl;
  
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
  tree.traversePreOrder([](const int& value) { cout << value << " "; });
  cout << endl;
  
  cout << "Inorder traversal  : ";
  tree.traverseInOrder([](const int& value) { cout << value << " "; });
  cout << endl;

  cout << "Postorder traversal: ";
  tree.traversePostOrder([](const int& value) { cout << value << " "; });
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
  result += testAVLTree();
  cout << "Failed Tests " << result << endl;
  return result;
}
