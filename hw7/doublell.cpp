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
  delete [] head;
  delete [] tail;
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
  DLink* newlink;
  newlink->data = what;
  newlink->next = NULL;
  newlink->prev = NULL;
  if (where == NULL)
  {
    // check if list is empty
    if (tail == NULL)
    {
      tail = newlink;
      head = newlink;
    }
    else
    {
      tail->next = newlink;
      newlink->prev = tail;
      tail = newlink;
    }
  }
  else
  {
    // I may be inserting after not before
    DLink* oldnext = where->next;
    where->next = newlink;
    newlink->prev = where;
    newlink->next = oldnext;
    oldnext->prev = newlink;
  }
}
string DoubleLL::remove(DLink* where)
{
  return "";
}
int DoubleLL::size() const
{
  int length = 0;
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
    if (current == NULL)
    {
      return "";
    }
    current = current->next;
  }
  return current->data;
}
