#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void Solution(bool aPartTwo);
void PartOne();
void PartTwo();

enum Dir
{
  East,
  SouthEast,
  SouthWest,
  West,
  NorthWest,
  NorthEast
};

struct Point
{
  Point & operator+=(const Point & aPoint)
  {
    x += aPoint.x;
    y += aPoint.y;

    return *this;
  }

  bool operator<(const Point & aPoint) const
  {
    return x < aPoint.x || (x == aPoint.x && y < aPoint.y);
  }

  int x{ 0 };
  int y{ 0 };
};

map<Dir, Point> dirPointMap = { { East, { 2, 0 } },        { SouthEast, { 1, -1 } },
                                { SouthWest, { -1, -1 } }, { West, { -2, 0 } },
                                { NorthWest, { -1, 1 } },  { NorthEast, { 1, 1 } } };

map<Point, bool> tilesMap;

int main()
{
  PartTwo();

  return 0;
}

Dir GetCurrentDir(const string & aSteps, int & aPos)
{
  Dir currentDir;

  if (aSteps[aPos] == 'e')
  {
    currentDir = East;
    aPos++;
  }
  else if (aSteps[aPos] == 'w')
  {
    currentDir = West;
    aPos++;
  }
  else if (aSteps[aPos] == 's')
  {
    if (aSteps[aPos + 1] == 'e')
    {
      currentDir = SouthEast;
      aPos += 2;
    }
    else if (aSteps[aPos + 1] == 'w')
    {
      currentDir = SouthWest;
      aPos += 2;
    }
  }
  else if (aSteps[aPos] == 'n')
  {
    if (aSteps[aPos + 1] == 'e')
    {
      currentDir = NorthEast;
      aPos += 2;
    }
    else if (aSteps[aPos + 1] == 'w')
    {
      currentDir = NorthWest;
      aPos += 2;
    }
  }

  return currentDir;
}

int CountAdjacent(const Point & aPoint, const map<Point, bool> & aTilesMap)
{
  int count = 0;

  for (int i = 0; i < 6; i++)
  {
    Point newPoint = aPoint;
    newPoint += dirPointMap[(Dir)i];

    if (aTilesMap.find(newPoint) == aTilesMap.end())
      continue;

    if (aTilesMap.at(newPoint) == false)
      count++;
  }

  return count;
}

void SetWhiteTiles(const Point & aPoint, map<Point, bool> & aTilesMap)
{
  for (int i = 0; i < 6; i++)
  {
    Point newPoint = aPoint;
    newPoint += dirPointMap[(Dir)i];

    if (aTilesMap.find(newPoint) == aTilesMap.end())
      aTilesMap[newPoint] = true;
  }
}

void Solution(bool aPartTwo)
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto steps = reader.ReadStrings();

  for (const auto & step : steps)
  {
    int   pos = 0;
    Point p;

    while (pos < step.size())
    {
      Dir currentDir = GetCurrentDir(step, pos);
      p += dirPointMap[currentDir];
    }

    if (tilesMap.find(p) == tilesMap.end())
      tilesMap[p] = false;
    else
      tilesMap[p] = !tilesMap[p];
  }

  if (aPartTwo)
  {
    for (int i = 0; i < 100; i++)
    {
      auto tempTilesMap = tilesMap;

      for (auto & tile : tempTilesMap)
      {
        if (tile.second == false)
        {
          SetWhiteTiles(tile.first, tempTilesMap);
        }
      }

      for (auto & tile : tempTilesMap)
      {
        int adjCount = CountAdjacent(tile.first, tilesMap);

        if (tile.second == false)
        {
          if (adjCount == 0 || adjCount > 2)
            tile.second = true;
        }
        else
        {
          if (adjCount == 2)
            tile.second = false;
        }
      }

      tilesMap = tempTilesMap;
    }
  }

  int count = 0;

  for (auto & tile : tilesMap)
  {
    if (tile.second == false)
      count++;
  }

  cout << count;
}

void PartOne()
{
  Solution(false);
}

void PartTwo()
{
  Solution(true);
}
