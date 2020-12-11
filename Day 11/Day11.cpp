#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void PartOne();
void PartTwo();

int rowCount = 0, colCount = 0;

int AdjCount(const vector<vector<char>> & aMatrix, int i, int j)
{
  int count = 0;

  if (i > 0)
  {
    if (aMatrix[i - 1][j] == '#')
      count++;

    if (j < colCount - 1 && aMatrix[i - 1][j + 1] == '#')
      count++;

    if (j > 0 && aMatrix[i - 1][j - 1] == '#')
      count++;
  }

  if (i < rowCount - 1)
  {
    if (aMatrix[i + 1][j] == '#')
      count++;

    if (j < colCount - 1 && aMatrix[i + 1][j + 1] == '#')
      count++;

    if (j > 0 && aMatrix[i + 1][j - 1] == '#')
      count++;
  }

  if (j > 0 && aMatrix[i][j - 1] == '#')
    count++;

  if (j < colCount - 1 && aMatrix[i][j + 1] == '#')
    count++;

  return count;
}

int AdjCount1(const vector<vector<char>> & aMatrix, int i, int j)
{
  int count = 0;

  if (i > 0)
  {
    int k = i - 1;
    while (k >= 0)
    {
      if (aMatrix[k][j] == '#')
      {
        count++;
        break;
      }
      else if (aMatrix[k][j] == 'L')
        break;
      else
        k--;
    }

    if (j < colCount - 1)
    {
      k     = i - 1;
      int l = j + 1;

      while (k >= 0 && l < colCount)
      {
        if (aMatrix[k][l] == '#')
        {
          count++;
          break;
        }
        else if (aMatrix[k][l] == 'L')
          break;
        else
        {
          k--;
          l++;
        }
      }
    }

    if (j > 0)
    {
      k     = i - 1;
      int l = j - 1;

      while (k >= 0 && l >= 0)
      {
        if (aMatrix[k][l] == '#')
        {
          count++;
          break;
        }
        else if (aMatrix[k][l] == 'L')
          break;
        else
        {
          k--;
          l--;
        }
      }
    }
  }

  if (i < rowCount - 1)
  {
    int k = i + 1;
    while (k < colCount)
    {
      if (aMatrix[k][j] == '#')
      {
        count++;
        break;
      }
      else if (aMatrix[k][j] == 'L')
        break;
      else
        k++;
    }

    if (j < colCount - 1)
    {
      k     = i + 1;
      int l = j + 1;

      while (k < colCount && l < colCount)
      {
        if (aMatrix[k][l] == '#')
        {
          count++;
          break;
        }
        else if (aMatrix[k][l] == 'L')
          break;
        else
        {
          k++;
          l++;
        }
      }
    }

    if (j > 0)
    {
      k     = i + 1;
      int l = j - 1;

      while (k < colCount && l >= 0)
      {
        if (aMatrix[k][l] == '#')
        {
          count++;
          break;
        }
        else if (aMatrix[k][l] == 'L')
          break;
        else
        {
          k++;
          l--;
        }
      }
    }
  }

  if (j > 0)
  {
    int k = j - 1;
    while (k >= 0)
    {
      if (aMatrix[i][k] == '#')
      {
        count++;
        break;
      }
      else if (aMatrix[i][k] == 'L')
        break;
      else
        k--;
    }
  }

  if (j < colCount - 1)
  {
    int k = j + 1;
    while (k <= colCount - 1)
    {
      if (aMatrix[i][k] == '#')
      {
        count++;
        break;
      }
      else if (aMatrix[i][k] == 'L')
        break;
      else
        k++;
    }
  }

  return count;
}

int main()
{
  PartOne();

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
        if (matrix[i][j] == 'L' && AdjCount1(matrix, i, j) == 0)
        {
          matrix1[i][j] = '#';
        }
        else if (matrix[i][j] == '#' && AdjCount1(matrix, i, j) >= 5)
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
