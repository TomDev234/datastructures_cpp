//
//  TestAVLTree.cpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#include "TestAVLTree.hpp"

#include <iostream>
#include "avl_tree.hpp"

using namespace std;

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
