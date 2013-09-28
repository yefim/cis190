#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool is_header(char b[])
{
  const int header[2][4] = { 
                             { 0xff, 0xd8, 0xff, 0xe0 },
                             { 0xff, 0xd8, 0xff, 0xe1 }
                           };
  int c = 0;
  for (int i = 0; i < 4; i++)
  {
    unsigned char ch = (unsigned char)b[i];
    if (!(header[0][i] == (int)ch && header[1][i] == (int)ch))
      return false;
  }
  return true;
}

string filename(int count)
{
  stringstream ss;
  ss << count;
  string num = ss.str();
  for (int i = num.length(); i < 3; i++)
  {
    num = "0" + num;
  }
  return num + ".jpg";
}

int main()
{
  cout << "What is the name of the file storing the flash card data? ";
  string input_file;
  getline(cin, input_file);

  ifstream evidence;
  evidence.open(input_file.c_str());

  if (!evidence)
  {
    cout << "Cannot read from " << input_file << endl;
    return 1;
  }

  int header[3] = { 0xff, 0xd8, 0xff };
  int last[2] = { 0xe0, 0xe1 };

  int counter = 1;
  char buffer[1];
  while(evidence.read(buffer, 1))
  {
    unsigned char ch = (unsigned char)buffer[0];
    if (header[0] == (int)ch && evidence.read(buffer,1))
    {
      unsigned char next = (unsigned char)buffer[0];
      if (header[1] == (int)next && evidence.read(buffer, 1))
      {
        unsigned char nextnext = (unsigned char)buffer[0];
        if (header[2] == (int)nextnext && evidence.read(buffer, 1))
        {
          unsigned char nnn = (unsigned char)buffer[0];
          if (last[0] == (int)nnn || last[1] == (int)nnn)
          {
            char first_header[4] = { (char)ch, (char)next, (char)nextnext, (char)nnn };
            char jpeg_buffer[508];
            evidence.read(jpeg_buffer, 508);

            ofstream out;
            out.open(filename(counter).c_str());
            out.write(first_header, 4);
            out.write(jpeg_buffer, 508);
            // read 4, then 508, then 4 then 508
            char head_buffer[4];
            while (evidence.read(head_buffer, 4) && evidence.read(jpeg_buffer, 508))
            {
              // new jpeg, close old one, open new one
              if (is_header(head_buffer))
              {
                out.close();
                counter++;
                out.open(filename(counter).c_str());
              }
              out.write(head_buffer, 4);
              out.write(jpeg_buffer, 508);
            }
            out.close();
          }
        }
      }
    }
  }
  cout << "Recovered " << counter << " jpegs from " << input_file << "..." << endl;
  evidence.close();
  return 0;
}
