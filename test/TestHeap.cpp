//
//  TestHeap.cpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#include "TestHeap.hpp"

#include <iostream>
#include "heap.hpp"

using namespace std;

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
