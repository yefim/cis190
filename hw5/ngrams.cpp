#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void init_rand()
{
  srand(time(NULL));
}
int rand_up_to(int limit)
{
  return (int)((double)rand() / RAND_MAX * limit);
}

int main()
{
  init_rand();
  cout << "What file would you like to ngram? ";
  string filename;
  cin >> filename;
  
  cout << "How many words per gram? ";
  int length;
  cin >> length;
  cout << endl;

  ifstream input(filename.c_str());
  if (!input)
  {
    cout << "Could not open " << filename << endl;
    return 1;
  }

  multimap<string, string> ngrams;
  typedef multimap<string, string>::iterator itor;

  // dump entire file into a vector
  vector<string> all_the_words;
  string word;
  while (input >> word)
  {
    all_the_words.push_back(word);
  }

  for (int j = 0; j < all_the_words.size() - length; j++)
  {
    string key = "";
    for (int i = j; i < j + length - 1; i++)
    {
      key = key + all_the_words.at(i) + " ";
    }
    string value = all_the_words.at(j + length - 1);
    ngrams.insert(make_pair(key, value));
  }
  
  // get random first key
  int first_index = rand_up_to(ngrams.size());
  string word_key;
  int current = 0;
  for (itor it = ngrams.begin(); it != ngrams.end(); it++, current++)
  {
    if (first_index == current)
    {
      word_key = it->first;
      break;
    }
  }

  string output = word_key;
  int len = length - 1;
  while(len < 100)
  {
    pair<itor, itor> range = ngrams.equal_range(word_key);
    if (range.first != range.second)
    {
      vector<string> vals;
      for (itor i = range.first; i != range.second; i++)
      {
        vals.push_back(i->second);
      }
      int r = rand_up_to(vals.size());
      string next = vals.at(r);
      output = output + next + " ";
      len++;
      // the new key is the old key minus the first word plus the old value
      int first_word = word_key.find_first_of(" ", 0) + 1;
      word_key = word_key.substr(first_word, word_key.size()) + next + " ";
    }
    else
    {
      break;
    }
  }
  cout << output << endl;

  return 0;
}
