//
//  TestStack.cpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#include "TestStack.hpp"

#include <iostream>
#include "stack.hpp"
#include "NumberNode.hpp"

using namespace std;

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
