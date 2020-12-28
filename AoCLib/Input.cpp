#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;

vector<vector<char>> InputReader::ReadCharMatrix()
{
  vector<vector<char>> matrix;

  while (!mInput.eof())
  {
    string row;
    getline(mInput, row);

    auto chars = GetCharVector(row);

    matrix.push_back(chars);
  }

  return matrix;
}

vector<string> InputReader::ReadMatrix()
{
  vector<string> matrix;

  while (!mInput.eof())
  {
    string row;
    getline(mInput, row);

    matrix.push_back(row);
  }

  return matrix;
}
