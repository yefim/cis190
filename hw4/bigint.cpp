#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include "bigint.h"

using namespace std;

string to_s(int num)
{
  stringstream ss;
  ss << num;
  return ss.str();
}
// FUCK C++ STRING TO INTERGER CONVERSION
// YES I KNOW I CAN DO THIS WITH A FOR LOOP
int to_i(const char &num)
{
  if (num == '0') return 0;
  if (num == '1') return 1;
  if (num == '2') return 2;
  if (num == '3') return 3;
  if (num == '4') return 4;
  if (num == '5') return 5;
  if (num == '6') return 6;
  if (num == '7') return 7;
  if (num == '8') return 8;
  if (num == '9') return 9;
  else return 0;
}


BigInt::BigInt()
{
  for (int i = 0; i < num_digits; i++)
  {
    digits[i] = 0;
  }
  negative = false;
}
BigInt::BigInt(int n)
{
  for (int i = 0; i < num_digits; i++)
  {
    digits[i] = 0;
  }
  if (n < 0)
  {
    negative = true;
    n = -n;
  } else {
    negative = false;
  }
  string num = to_s(n);
  int len = num.length();
  for (int i = 0; i < len; i++)
  {
    digits[num_digits-i-1] = to_i(num[len-i-1]);
  }
}
BigInt::BigInt(long n)
{
}
BigInt::BigInt(const BigInt& bi)
{
  negative = bi.negative;
  for (int i = 0; i < num_digits; i++)
  {
    digits[i] = bi.digits[i];
  }
}
BigInt BigInt::operator+() const
{
  return *this;
}
BigInt BigInt::operator-() const
{
  BigInt copy(*this);
  copy.negative = !negative;
  return copy;
}
BigInt BigInt::operator+(const BigInt& bi) const
{
  BigInt result(*this);
  result += bi;
  return result;
}
BigInt BigInt::operator-(const BigInt& bi) const
{
  BigInt result(*this);
  result += -bi;
  return result;
}
BigInt BigInt::operator*(const BigInt& bi) const
{
  BigInt result(*this);
  for (int i = 0; i < num_digits; i++)
  {
    int upto = digits[i] * pow(10, num_digits - i - 1);
    for (int j = 0; j < upto; j++)
    {
      result += result;
    }
  }
  return result;
}
void BigInt::operator=(const BigInt& bi)
{
  negative = bi.negative;
  for (int i = 0; i < num_digits; i++)
  {
    digits[i] = bi.digits[i];
  }
}
void BigInt::operator+=(const BigInt& bi)
{
  int carry = 0;
  for (int i = 0; i < num_digits; i++)
  {
    int sum = digits[i] + bi.digits[i] + carry;
    carry = sum / 10;
    digits[i] = sum % 10;
  }
}
void BigInt::operator-=(const BigInt& bi)
{
}
void BigInt::operator*=(const BigInt& bi)
{
}
bool BigInt::operator==(const BigInt& bi) const
{
  bool all_zeroes = true; // assume true
  bool equal = negative == bi.negative;
  for (int i = 0; i < num_digits; i++)
  {
    if (digits[i] == bi.digits[i] && digits[i] != 0)
      all_zeroes = false;
    if (digits[i] != bi.digits[i])
    {
      equal = false;
    }
  }
  if (all_zeroes) return true;
  return equal;
}
bool BigInt::operator!=(const BigInt& bi) const
{
  return !(*this == bi);
}
bool BigInt::operator<(const BigInt& bi) const
{
  // check negatives
  if (negative && !bi.negative) return true;
  if (!negative && bi.negative) return false;
  bool both_neg = false;
  if (negative && bi.negative) both_neg = true;

  for (int i = 0; i < num_digits; i++)
  {
    if (digits[i] < bi.digits[i])
      if (both_neg) return false;
      else return true;
    if (digits[i] > bi.digits[i])
      if (both_neg) return true;
      else return false;
  }
  return false;
}
bool BigInt::operator<=(const BigInt& bi) const
{
  return *this < bi || *this == bi;
}
bool BigInt::operator>(const BigInt& bi) const
{
  return !(*this <= bi);
}
bool BigInt::operator>=(const BigInt& bi) const
{
  return !(*this < bi);
}

// inBigInt::crement/decrement
void BigInt::operator++()
{
  *this += 1;
}
void BigInt::operator--()
{
  *this -= 1;
}
void BigInt::operator++(int)
{
}
void BigInt::operator--(int)
{
}

// conversions -- they return 0 when invalid (out of range)
BigInt::operator int() const
{
  // int max = 13246;
  int num = 0;
  for (int i = 0; i < num_digits; i++)
  {
    num = num + digits[i] * pow(10, num_digits - i - 1);
  }
  if (negative)
    num = -num;
  return num;
}
BigInt::operator long() const
{
  return 0L;
}

// print a BigInt:
ostream& operator<<(ostream& out, const BigInt& bi)
{
  string num;
  if (bi.negative)
  {
    num = "-";
  } else {
    num = "";
  }
  for (int i = 0; i < bi.num_digits; i++)
  {
    if (bi.digits[i] != 0)
      num += to_s(bi.digits[i]);
  }
  out << num;
  return out;
}
