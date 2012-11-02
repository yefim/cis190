/* File: double.h
 * Author: Geoffrey (veg)
 * Desc: interface for double linked list class
 */

#ifndef DOUBLELL_H_
#define DOUBLELL_H_

#include <iostream>

struct DLink
{
  std::string data;
  DLink* prev;
  DLink* next;
};

class DoubleLL
{
 private:
  DLink* head;
  DLink* tail;
 public:
  DoubleLL();
  ~DoubleLL();
  DLink* getHead() const;
  DLink* getTail() const;
  void insert(DLink* where, const std::string& what);
  std::string remove(DLink* where);
  int size() const;
  std::string nth(int n) const;
};

#endif
