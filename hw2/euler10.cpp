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
  long sum = 0;
  for (long i = 2; i < 2000000; i++)
  {
    if (isPrime(i))
    {
      sum += i;
    }
  }
  cout << sum << endl;
  return 0;
}
