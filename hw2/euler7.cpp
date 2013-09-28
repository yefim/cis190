#include <iostream>
#include <math.h>

using namespace std;

bool isPrime(long p) {
  if (p == 2)
    return true;
  for (int i = 2; i < sqrt(p) + 1; i++)
  {
    if (p % i == 0)
      return false;
  }
  return true;
}

int main()
{
  int count = 0;
  long num = 1;
  while (count < 10001) {
    if (isPrime(++num))
    {
      count++;
    }
  }
  cout << num << endl;
  return 0;
}
