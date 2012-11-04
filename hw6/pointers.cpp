/* File: pointers.cpp
   Author: Richard Eisenberg (eir@cis) and Geoffrey Vedernikoff (veg@cis)
   Desc: CIS190, assignment 6
*/

/* CIS190: Homework Assignment 6, due Friday 10/19, at 11:59pm
   10 points total */

/* Please complete all the exercises in this file. Make sure to obey any
   particular rules (i.e. use index notation, or don't use index notation,
   etc.) for a given exercise. If you do not complete the rules, you get
   no credit for the assignment. */

#include <iostream>
using namespace std;

/************ C-STYLE STRINGS ***********/

/* A C-style string is a region of memory with the characters forming the
   string in order, followed by a character of value 0. Note that the
   character of value 0 is distinct from '0', the ASCII digit representing
   zero. ('0' actually has the value 48.) Another way to write the character
   of value 0 is '\0'.

   Because it is possible to identify the end of a string, strings are often
   passed to functions and stored in variables just as a char*. Here, you will
   write some basic string functions. You _may not_ use index notation (with
   brackets []) in any of these functions. You also _may not_ use any C++ or C
   library functions. You _may_ use helper functions and earlier problems in
   later ones. */

/* string_len returns the length of a string. The length of a string does not
   count the terminating 0. (.5 points) */
int string_len(const char* str)
{
  int length = 0;
  for (; *str != '\0'; str++, length++);
  return length;
}

/* string_copy copies a string from 'src' to 'dest'. It is assumed that 'dest'
   points to a region of memory capable of storing the string in 'src'.
   (.5 points) */
void string_copy(char* dest, const char* src)
{
  for (; (*dest = *src); src++, dest++);
}


/* print_vert prints out every character in a string, one per line. 
   (.5 points) */
void print_vert(const char* str)
{
  for(; *str != '\0'; str++)
  {
    cout << *str << endl;
  }
}

/* swap_strings swaps the contents of two strings in memory. Because each
   region in memory has a specific size and we don't want to write outside of
   a region, this function can only work if the lengths of the strings are the
   same. So, if the lengths are the same, it swaps the contents and returns
   true; otherwise it just returns false and does not change the contents of
   memory. (1 point) */
bool swap_strings(char* a, char* b)
{
  if (string_len(a) != string_len(b))
  {
    return false;
  }
  for (; *a != '\0'; a++, b++)
  {
    char tmp = *a;
    *a = *b;
    *b = tmp;
  }
  return true;
}

/* insert_stars puts a star character ('*') between every two adjacent letters
   that are the same. You can assume that the region of memory storing the
   string is large enough to accommodate the extra characters. So, the string
   "abcd" does not change, "aaa" becomes "a*a*a" and "abaab" becomes "aba*ab".
   It returns the number of stars added. (2 points) */
int insert_stars(char* str)
{
  int stars = 0;
  for (; *str != '\0'; str++)
  {
    char first = *str;
    char second = *(str + 1);
    if (first == second)
    {
      stars++;
      *(str+1) = '*';
    }
  }
  return stars;
}

/* count_as takes an array of strings and prints out the total number of 'a'
   characters (just lowercase ones) in all the strings. The array is passed in
   using (as usual) a pointer. However, since a string is really just a char*,
   a pointer to a string is a char**. Of course, an array does not have a
   terminating 0, so we must also pass in the length of this array. Note that
   the strings themselves may be of different lengths.

   Say the function receives the pointer p and a length of 5. That means that
   p points to a region of memory containing 5 pointers to characters. So, *p
   is a pointer to the first character in the first string. *(p + 1) is a
   pointer to the first character in the second string. (*p) + 1 is a pointer
   to the second character in the first string. **p is the first character in
   the first string.

   (1.5 points)
*/
int count_as(const char *const * p, int num_strings)
{
  int as = 0;
  for (int i = 0; i < num_strings; i++, p++)
  {
    for (int j = 0; j < string_len(*p); j++)
    {
      if (*(*p + j) == 'a')
      {
        as++;
      }
    }
  }
  return as;
}

/* From here on down, you _may_ use the index notation (using []) as you wish.
 */

/*********** RESIZABLE ARRAY ****************/

/* One of the main drawbacks of a traditional C++ array is that it cannot
resize. We will remedy this by writing a short class that stores a growable
array of ints. Here is the definition of the class: */

class vector
{
 private:
  int* data; // pointer to the region of data
  int length; // the number of ints stored

 public:
  vector(); // initializes vector with 0 elements
  ~vector(); // deallocates the array

  // If n is a valid index, returns a pointer to the nth element (counting
  // from 0). If n is not a valid index, returns NULL. This function is useful
  // if a user of our vector class wished to change the value of an element in
  // the vector. They could say *(v.get_ptr(n)) = foo;
  int* get_ptr(int n);

  // if n is a valid index, returns the nth element (counting from 0)
  // if n is not a valid index, prints an error and returns -1
  // (Note that this error behavior is a terrible design for a real
  // system.)
  int operator[](int n);

  // adds a new element to the end of the vector
  void add(int x);
};

/* So, how do we make a resizable array? Well, we can't, so we have to fake
   it. Every region of memory in a C++ program has a fixed size, chosen when
   the memory is allocated. When we need more memory than we have, we have to
   allocate a totally new region of memory of the desired size, copy all the
   data into the new region, and the deallocate the old region. That's exactly
   what your add function will have to do. */

// (.5 points)
vector::vector()
{
  length = 0;
  data = new int[length];
}

// (.5 points)
// Remember, the destructor is called when we are done with an object. It
// should deallocate any memory used by the object.
vector::~vector()
{
  delete [] data;
}

// (1 points)
int* vector::get_ptr(int n)
{
  if (n >= length)
  {
    return NULL;
  }
  else
  {
    return (data + n);
  }
}

// (.5 points)
int vector::operator[](int n)
{
  if (n >= length)
  {
    cout << "Index out of bounds error" << endl;
    return -1;
  }
  else
  {
    return *(data + n);
  }
}

// (1 point)
void vector::add(int x)
{
  int* resized = new int[length+1];
  for (int i = 0; i < length; i++)
  {
    resized[i] = data[i];
  }
  resized[length] = x;
  length++;
  data = resized;
  delete [] resized;
}


/************ TESTING YOUR WORK *************/

/* Write a main function that tests your work above. While we won't be too
   strict when grading this, it is in your best interest to test thoroughly!
   (.5 points)
*/
int main()
{
  const char *hello = "hello";
  cout << string_len(hello) << endl;

  char world[] = {"world"};
  string_copy(world, hello);
  cout << world << endl;
  
  print_vert(world);

  char johny[] = {"johny"};
  swap_strings(world, johny);
  cout << "world: " << world << endl;
  cout << "johny: " << johny << endl;

  char well[] = {"well"};
  insert_stars(well);

  const char *arr[3] = { "adsadsadba", "aaa", "ccc" };
  int num = count_as(arr, 3);
  cout << "Number of a's: " << num << endl;

  vector a;
  a.add(20);
  cout << a[0] << endl;

  return 0;
}
