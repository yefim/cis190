/* File: bigint.h
   Author: Richard Eisenberg (eir@cis)
   Desc: interface for big integer class
*/

#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>

class BigInt
{
 private:
  static const int num_digits = 100;
  int digits[num_digits];
  bool negative;

 public:
  BigInt(); // initializes to 0
  BigInt(int n);
  BigInt(long l);

  BigInt(const BigInt& bi); // copy constructor

  BigInt operator+() const; // noop operator -- it does nothing!
  BigInt operator-() const; // negation

  // basic arithmetic
  BigInt operator+(const BigInt& bi) const;
  BigInt operator-(const BigInt& bi) const;
  BigInt operator*(const BigInt& bi) const;

  // assignment
  void operator=(const BigInt& bi);

  // compound assignment (recall: a += b is equivalent to a = a + b)
  void operator+=(const BigInt& bi);
  void operator-=(const BigInt& bi);
  void operator*=(const BigInt& bi);

  // comparisons
  bool operator==(const BigInt& bi) const;
  bool operator!=(const BigInt& bi) const;
  bool operator<(const BigInt& bi) const;
  bool operator<=(const BigInt& bi) const;
  bool operator>(const BigInt& bi) const;
  bool operator>=(const BigInt& bi) const;

  // increment/decrement
  void operator++();
  void operator--();
  void operator++(int); // suffix
  void operator--(int); // suffix

  // conversions -- they return 0 when invalid (out of range)
  operator int() const;
  operator long() const;

  // print a BigInt:
  friend std::ostream& operator<<(std::ostream& out, const BigInt& bi);

};

#endif
