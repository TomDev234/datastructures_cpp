//
//  TestQueue.cpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#include "TestQueue.hpp"

#include <iostream>
#include "queue.hpp"
#include "NumberNode.hpp"

using namespace std;

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
