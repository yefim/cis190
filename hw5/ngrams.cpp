#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
  cout << "What file would you like to ngram? ";
  string filename = "p-and-p.txt";
  // cin >> filename;
  
  cout << "How many words per gram? ";
  int length = 2;
  // cin >> length;
  cout << endl;

  ifstream input(filename.c_str());
  if (!input)
  {
    cout << "Could not open " << filename << endl;
    return 1;
  }

  multimap<string, string> ngrams;
  typedef multimap<string, string>::iterator itor;

  string *words = new string[length];
  while (input)
  {
    for (int i = 0; i < length; i++)
    {
      string word;
      input >> word; // while this
      words[i] = word;
    }
    // add it to the map
    string key = "";
    string value = words[length-1];
    for (int i = 0; i < length - 1; i++)
    {
      key = key + words[i] + " ";
    }
    ngrams.insert(make_pair(key, value));
    // cout << key << endl;
  }

  string output;
  int len = 0;
  itor previous = ngrams.find("hear "); // must be random
  // add previous's key and value to output
  output = previous->first + previous->second;
  // string word_key; // could set and change this key everytime
  while(len < 100)
  {
    // the new key is the old key minus the first word plus the old value
    // int first_space = 0;
    string key = previous->first + previous->second;
    itor current = ngrams.find(key);
    if (current != ngrams.end())
    {
      output = output + current->second;
      len++;
    }
    else
    {
      break;
    }
  }

  cout << output << endl;

  delete [] words;
  return 0;
}
