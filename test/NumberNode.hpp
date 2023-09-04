//
//  NumberNode.hpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#ifndef NumberNode_hpp
#define NumberNode_hpp

#include <ostream>
#include <string>

using namespace std;

class NumberNode {
public:
  virtual ~NumberNode() = default;
  virtual string toString() const = 0;
  // Virtual function for the << operator
  virtual ostream& print(ostream& stream) const;
  // Friend function to use the virtual function
  friend ostream& operator << (ostream& stream, const NumberNode& node) {
    return node.print(stream);
  }
  virtual bool lessOrEqual(const NumberNode& node) const = 0;
  // Overload the <= operator
  bool operator <= (const NumberNode& other) const {
    return this->lessOrEqual(other);
  }
  virtual bool greaterThan(const NumberNode& node) const = 0;
  // Overload the <= operator
  bool operator > (const NumberNode& other) const {
    return this->greaterThan(other);
  }
};

class IntNode : public NumberNode {
public:
  int value;
  IntNode() : value(0) {}
  IntNode(int value) : value(value) {}
  string toString() const override {
    return to_string(value);
  }
  // Override the virtual function
  ostream& print(ostream& stream) const override;
  bool lessOrEqual(const NumberNode& other) const override;
  bool greaterThan(const NumberNode& other) const override;
};

class FloatNode : public NumberNode {
public:
  float value;
  FloatNode() : value(0) {}
  FloatNode(float value) : value(value) {}
  string toString() const override {
    return to_string(value);
  }
  // Override the virtual function
  ostream& print(ostream& stream) const override;
  bool lessOrEqual(const NumberNode& other) const override;
  bool greaterThan(const NumberNode& other) const override;
};

#endif /* NumberNode_hpp */
