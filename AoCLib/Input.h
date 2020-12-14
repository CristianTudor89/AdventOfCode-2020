#pragma once

#include "stdafx.h"

class InputReader
{
public:
  InputReader(ifstream & aInput)
    : mInput(aInput)
  {
  }

  // Read values (one on a line)
  // No new line is needed
  template <class T = int>
  vector<T> ReadValues()
  {
    vector<T> values;

    while (!mInput.eof())
    {
      T value;
      mInput >> value;

      values.push_back(value);
    }

    return values;
  }

  // Read strings with spaces (one on a line)
  // No new line is needed
  vector<string> ReadStrings()
  {
    vector<string> values;

    while (!mInput.eof())
    {
      string value;
      getline(mInput, value);

      values.push_back(value);
    }

    return values;
  }

  // Read values (using a separator)
  // No new line is needed
  template <class T = int>
  vector<T> ReadValues(const string & aSeparator)
  {
    string fullValue;
    getline(mInput, fullValue);

    vector<T> values;
    size_t    initialPos = 0, pos = 0;

    while (pos != string::npos)
    {
      string str;

      pos = fullValue.find(aSeparator, initialPos);
      if (pos == string::npos)
      {
        str = fullValue.substr(initialPos);
      }
      else
      {
        str        = fullValue.substr(initialPos, pos - initialPos);
        initialPos = pos + aSeparator.size();
      }

      T            value;
      stringstream convert(str);
      convert >> value;

      values.push_back(value);
    }

    return values;
  }

  vector<vector<char>> ReadCharMatrix();

private:
  ifstream & mInput;
};
