#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

int rowCount = 0, colCount = 0;

struct Point
{
  Point(int x, int y)
    : x(x)
    , y(y)
  {
  }

  bool IsInBounds() const { return x >= 0 && x < rowCount && y >= 0 && y < colCount; }

  int x;
  int y;
};

vector<Point> dirs = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 },
                       { 0, 1 },   { 1, -1 }, { 1, 0 },  { 1, 1 } };

void PartOne();
void PartTwo();

int AdjCount(const vector<vector<char>> & aMatrix, int i, int j)
{
  int count = 0;

  for (const auto & dir : dirs)
  {
    Point nextPoint(i + dir.x, j + dir.y);

    if (nextPoint.IsInBounds())
    {
      if (aMatrix[nextPoint.x][nextPoint.y] == '#')
        count++;
    }
  }

  return count;
}

int DirCount(const vector<vector<char>> & aMatrix, int i, int j)
{
  int count = 0;

  for (const auto & dir : dirs)
  {
    Point nextPoint(i + dir.x, j + dir.y);

    while (nextPoint.IsInBounds())
    {
      if (aMatrix[nextPoint.x][nextPoint.y] == '#')
      {
        count++;
        break;
      }
      else if (aMatrix[nextPoint.x][nextPoint.y] == 'L')
        break;
      else
      {
        nextPoint.x += dir.x;
        nextPoint.y += dir.y;
      }
    }
  }

  return count;
}

int main()
{
  PartTwo();

  return 0;
}

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto matrix = reader.ReadCharMatrix();

  rowCount = matrix.size();
  colCount = matrix[0].size();

  while (true)
  {
    auto matrix1 = matrix;

    for (int i = 0; i < rowCount; i++)
    {
      for (int j = 0; j < colCount; j++)
      {
        if (matrix[i][j] == 'L' && AdjCount(matrix, i, j) == 0)
        {
          matrix1[i][j] = '#';
        }
        else if (matrix[i][j] == '#' && AdjCount(matrix, i, j) >= 4)
        {
          matrix1[i][j] = 'L';
        }
      }
    }

    bool found = true;
    for (int i = 0; i < rowCount; i++)
    {
      for (int j = 0; j < colCount; j++)
        if (matrix[i][j] != matrix1[i][j])
          found = false;
    }

    if (found)
    {
      int count = 0;
      for (int i = 0; i < rowCount; i++)
      {
        for (int j = 0; j < colCount; j++)
          if (matrix[i][j] == '#')
            count++;
      }

      cout << count;
      break;
    }
    else
    {
      matrix = matrix1;
    }
  }
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto matrix = reader.ReadCharMatrix();

  rowCount = matrix.size();
  colCount = matrix[0].size();

  while (true)
  {
    auto matrix1 = matrix;

    for (int i = 0; i < rowCount; i++)
    {
      for (int j = 0; j < colCount; j++)
      {
        if (matrix[i][j] == 'L' && DirCount(matrix, i, j) == 0)
        {
          matrix1[i][j] = '#';
        }
        else if (matrix[i][j] == '#' && DirCount(matrix, i, j) >= 5)
        {
          matrix1[i][j] = 'L';
        }
      }
    }

    bool found = true;
    for (int i = 0; i < rowCount; i++)
    {
      for (int j = 0; j < colCount; j++)
        if (matrix[i][j] != matrix1[i][j])
          found = false;
    }

    if (found)
    {
      int count = 0;
      for (int i = 0; i < rowCount; i++)
      {
        for (int j = 0; j < colCount; j++)
          if (matrix[i][j] == '#')
            count++;
      }

      cout << count;
      break;
    }
    else
    {
      matrix = matrix1;
    }
  }
}
