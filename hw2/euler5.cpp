#include <iostream>

using namespace std;

bool divisible(long num) {
  for (int i = 1; i <= 20; i++)
  {
    if (num % i != 0)
      return false;
  }
  return true;
}

int main()
{
  long num = 0;
  // while not divisible by all 20 numbers,
  // add one and try again
  while (!divisible(++num));
  cout << num << endl;
  return 0;
}
