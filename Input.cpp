#include "Input.h"

vector<char> InputReader::ReadChars(const string & aStr)
{
  vector<char> chars(aStr.size());

  for (size_t i = 0; i < aStr.size(); i++)
    chars[i] = aStr[i];

  return chars;
}

vector<vector<char>> InputReader::ReadCharMatrix()
{
  vector<vector<char>> matrix;

  while (!mInput.eof())
  {
    string row;
    getline(mInput, row);

    auto chars = ReadChars(row);

    matrix.push_back(chars);
  }

  return matrix;
}
