//
//  TestList.cpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#include "TestList.hpp"

#include <iostream>
#include "list.hpp"
#include "NumberNode.hpp"

using namespace std;

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
  list.addHead(make_shared<IntNode>(29));
  list.addTail(make_shared<IntNode>(20));
  list.addTail(make_shared<IntNode>(21));
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

  if(!list.isSorted())
    cout << "List is not sorted\n";
  else
    cout << "List is sorted\n";
  
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

  if (!list.isSorted()) {
    cout << "List not sorted Error!\n";
    result = 1;
  }
  else
    cout << "List is sorted.\n";
  
  cout << endl;
  
  return result;
}
