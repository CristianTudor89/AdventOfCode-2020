#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;

void PartOne();
void PartTwo();

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

  int posX = 0, posY = 0, trees = 0;
  int rowCount = matrix.size(), colCount = matrix[0].size();

  while (posX < rowCount - 1)
  {
    posX++;
    posY += 3;

    if (posY >= colCount)
      posY -= colCount;

    if (matrix[posX][posY] == '#')
      trees++;
  }

  cout << trees;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto matrix = reader.ReadCharMatrix();

  int rowCount = matrix.size(), colCount = matrix[0].size(), product = 1;

  vector<pair<int, int>> slopes = { { 1, 1 }, { 1, 3 }, { 1, 5 }, { 1, 7 }, { 2, 1 } };

  for (const auto & slope : slopes)
  {
    int posX = 0, posY = 0, trees = 0;

    while (posX < rowCount - 1)
    {
      posX += slope.first;
      posY += slope.second;

      if (posY >= colCount)
        posY -= colCount;

      if (matrix[posX][posY] == '#')
        trees++;
    }

    product *= trees;
  }

  cout << product;
}
