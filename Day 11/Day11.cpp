#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void PartOne();
void PartTwo();

int AdjCount(const vector<vector<char>> & aMatrix, int i, int j)
{
  int count = 0;
  if (i > 0)
  {
    if (aMatrix[i - 1][j] == '#')
      count++;

    if (j < aMatrix[0].size() - 1 && aMatrix[i - 1][j + 1] == '#')
      count++;

    if (j > 0 && aMatrix[i - 1][j - 1] == '#')
      count++;
  }

  if (i < aMatrix.size() - 1)
  {
    if (aMatrix[i + 1][j] == '#')
      count++;

    if (j < aMatrix[0].size() - 1 && aMatrix[i + 1][j + 1] == '#')
      count++;

    if (j > 0 && aMatrix[i + 1][j - 1] == '#')
      count++;
  }

  if (j > 0 && aMatrix[i][j - 1] == '#')
    count++;

  if (j < aMatrix[i].size() - 1 && aMatrix[i][j + 1] == '#')
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

    if (j < aMatrix[0].size() - 1)
    {
      k     = i - 1;
      int l = j + 1;

      while (k >= 0 && l < aMatrix[0].size())
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

  if (i < aMatrix.size() - 1)
  {
    int k = i + 1;
    while (k < aMatrix[0].size())
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

    if (j < aMatrix[0].size() - 1)
    {
      k     = i + 1;
      int l = j + 1;

      while (k < aMatrix[0].size() && l < aMatrix[0].size())
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

      while (k < aMatrix[0].size() && l >= 0)
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

  if (j < aMatrix[0].size() - 1)
  {
    int k = j + 1;
    while (k <= aMatrix[0].size() - 1)
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
  PartTwo();

  return 0;
}

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto matrix = reader.ReadCharMatrix();

  while (true)
  {
    auto matrix1 = matrix;

    for (int i = 0; i < matrix1.size(); i++)
    {
      for (int j = 0; j < matrix1[i].size(); j++)
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
    for (int i = 0; i < matrix1.size(); i++)
    {
      for (int j = 0; j < matrix1[i].size(); j++)
        if (matrix[i][j] != matrix1[i][j])
          found = false;
    }

    if (found)
    {
      int count = 0;
      for (int i = 0; i < matrix1.size(); i++)
      {
        for (int j = 0; j < matrix1[i].size(); j++)
          if (matrix[i][j] == '#')
            count++;
      }

      cout << count;
      break;
    }
    else
    {
      for (int i = 0; i < matrix1.size(); i++)
      {
        for (int j = 0; j < matrix1[i].size(); j++)
          matrix[i][j] = matrix1[i][j];
      }
    }
  }
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto matrix = reader.ReadCharMatrix();

  while (true)
  {
    auto matrix1 = matrix;

    for (int i = 0; i < matrix1.size(); i++)
    {
      for (int j = 0; j < matrix1[i].size(); j++)
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
    for (int i = 0; i < matrix1.size(); i++)
    {
      for (int j = 0; j < matrix1[i].size(); j++)
        if (matrix[i][j] != matrix1[i][j])
          found = false;
    }

    if (found)
    {
      int count = 0;
      for (int i = 0; i < matrix1.size(); i++)
      {
        for (int j = 0; j < matrix1[i].size(); j++)
          if (matrix[i][j] == '#')
            count++;
      }

      cout << count;
      break;
    }
    else
    {
      for (int i = 0; i < matrix1.size(); i++)
      {
        for (int j = 0; j < matrix1[i].size(); j++)
          matrix[i][j] = matrix1[i][j];
      }
    }
  }
}
