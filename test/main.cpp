//
//  main.cpp
//  datastructures_tests
//
//  Created by Tom on 07.08.23.
//

#include <iostream>
#include "TestStack.hpp"
#include "TestQueue.hpp"
#include "TestList.hpp"
#include "TestHeap.hpp"
#include "TestAVLTree.hpp"

using namespace std;

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
