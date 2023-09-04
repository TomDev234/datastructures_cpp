//
//  NumberNode.cpp
//  datastructures_cpp
//
//  Created by Tom on 04.09.23.
//

#include "NumberNode.hpp"

ostream& NumberNode::print(ostream& stream) const {
  stream << "NumberNode";
  return stream;
}

ostream& IntNode::print(ostream& stream) const {
  stream << toString();
  return stream;
}

bool IntNode::lessOrEqual(const NumberNode& other) const {
  bool result;
  const IntNode* otherInt = dynamic_cast<const IntNode*>(&other);
  if (otherInt != nullptr)
    result = value <= otherInt->value;
  else
    result = false;
  return result;
}

bool IntNode::greaterThan(const NumberNode& other) const {
  bool result;
  const IntNode* otherInt = dynamic_cast<const IntNode*>(&other);
  if (otherInt != nullptr)
    result = value > otherInt->value;
  else
    result = false;
  return result;
}

ostream& FloatNode::print(ostream& stream) const {
  stream << toString();
  return stream;
}

bool FloatNode::lessOrEqual(const NumberNode& other) const {
  bool result;
  const FloatNode* otherFloat = dynamic_cast<const FloatNode*>(&other);
  if(otherFloat != nullptr)
    result = value <= otherFloat->value;
  else
    result = false;
  return result;
}

bool FloatNode::greaterThan(const NumberNode& other) const {
  bool result;
  const FloatNode* otherFloat = dynamic_cast<const FloatNode*>(&other);
  if(otherFloat != nullptr)
    result = value > otherFloat->value;
  else
    result = false;
  return result;
}

