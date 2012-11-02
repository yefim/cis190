#include <iostream>
#include <string>
#include "doublell.h"

using namespace std;

DoubleLL::DoubleLL()
{
  head = NULL;
  tail = NULL;
}
DoubleLL::~DoubleLL()
{
  while (head)
  {
    DLink* next = head->next;
    delete head;
    head = next;
  }
}
DLink* DoubleLL::getHead() const
{
  return head;
}
DLink* DoubleLL::getTail() const
{
  return tail;
}
void DoubleLL::insert(DLink* where, const string& what)
{
  DLink* newlink = new DLink();
  newlink->data = what;
  if (!where)
  {
    // check if list is empty
    if (!tail)
    {
      newlink->next = NULL;
      newlink->prev = NULL;
      tail = newlink;
      head = newlink;
    }
    else
    {
      newlink->next = NULL;
      newlink->prev = tail;
      tail->next = newlink;
      tail = newlink;
    }
  }
  else
  {
    // check if inserting before head
    if (where == head)
    {
      where->prev = newlink;
      newlink->next = where;
      newlink->prev = NULL;
      head = newlink;
    }
    else
    {
      DLink* oldprev = where->prev;
      where->prev = newlink;
      newlink->next = where;
      newlink->prev = oldprev;
      oldprev->next = newlink;
    }
  }
}
string DoubleLL::remove(DLink* where)
{
  if (!where)
  {
    return "";
  }
  string data = where->data;
  // need to check if deleting head and/or tail
  if (where == head && where == tail)
  {
    head = NULL;
    tail = NULL;
  }
  else if (where == head)
  {
    head = where->next;
    head->prev = NULL;
  }
  else if (where == tail)
  {
    tail = tail->prev;
    tail->next = NULL;
  }
  else
  {
    DLink* prev = where->prev;
    DLink* next = where->next;
    prev->next = next;
    next->prev = prev;
  }
  delete where;
  return data;
}
int DoubleLL::size() const
{
  if (!tail)
  {
    return 0;
  }
  int length = 1;
  DLink* current = head;
  while (current != tail)
  {
    current = current->next;
    length++;
  }
  return length;
}
string DoubleLL::nth(int n) const
{
  int counter = 0;
  DLink* current = head;
  while (counter < n)
  {
    // checks for overflow
    if (!current)
    {
      return "";
    }
    current = current->next;
  }
  return current->data;
}
