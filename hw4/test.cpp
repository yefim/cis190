#include <iostream>
#include <string>
#include "bigint.h"

using namespace std;

int main()
{
  bool test[11];
  BigInt a;
  BigInt b(1);
  BigInt c(1L);
  BigInt d(a);

  // unary
  test[0] = a == +a;
  test[1] = a == -a;
  // arithmetic
  test[2] = a + b == b;
  test[3] = a - b == -b;
  test[4] = a * b == a;
  // assignment
  a = BigInt(10);
  test[5] = a == BigInt(10);
  // comparisons
  test[6] = a > b;
  test[7] = a >= b;
  test[8] = b < a;
  test[9] = b <= a;
  // conversions
  test[10] = (int)a == 10;
  
  for (int i = 0; i < 11; i++)
  {
    cout << i << ": " << test[i] << endl;
  }
  return 0;
}
