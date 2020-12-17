#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

struct Point
{
  Point(int x, int y, int z, int w)
    : x(x)
    , y(y)
    , z(z)
    , w(w)
  {
  }

  bool operator<(const Point & aPoint) const
  {
    return std::tie(x, y, z, w) < std::tie(aPoint.x, aPoint.y, aPoint.z, aPoint.w);
  }

  int x{ 0 };
  int y{ 0 };
  int z{ 0 };
  int w{ 0 };
};

map<Point, bool> points;

vector<Point> GetNeighbors(const Point & aPoint, bool aIs4Dimensional)
{
  vector<Point> neighbors;

  for (int x = -1; x <= 1; x++)
  {
    for (int y = -1; y <= 1; y++)
    {
      for (int z = -1; z <= 1; z++)
      {
        if (aIs4Dimensional)
        {
          for (int w = -1; w <= 1; w++)
          {
            if (x != 0 || y != 0 || z != 0 || w != 0)
              neighbors.push_back({ aPoint.x + x, aPoint.y + y, aPoint.z + z, aPoint.w + w });
          }
        }
        else
        {
          if (x != 0 || y != 0 || z != 0)
            neighbors.push_back({ aPoint.x + x, aPoint.y + y, aPoint.z + z, 0 });
        }
      }
    }
  }

  return neighbors;
}

bool IsActive(const Point & aPoint)
{
  auto it = points.find(aPoint);
  if (it == points.end())
    return false;

  return it->second;
}

int GetActiveCount(const Point & aPoint, bool aIs4Dimensional)
{
  int count = 0;

  for (const auto & neighbor : GetNeighbors(aPoint, aIs4Dimensional))
  {
    if (IsActive(neighbor))
      count++;
  }

  return count;
}

void PartOne();
void PartTwo();

int main()
{
  PartTwo();

  return 0;
}

void Solution(bool aIs4Dimensional)
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto matrix = reader.ReadCharMatrix();

  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[i].size(); j++)
    {
      Point point(i, j, 0, 0);
      points[point] = (matrix[i][j] == '#');
    }
  }

  for (int step = 0; step < 6; step++)
  {
    auto pointsToCheck{ points };

    for (const auto & [point, state] : points)
    {
      auto neighbors = GetNeighbors(point, aIs4Dimensional);
      for (const auto & neighbor : neighbors)
        pointsToCheck[neighbor] = IsActive(neighbor);
    }

    points = pointsToCheck;

    for (const auto & [point, state] : points)
    {
      int count = GetActiveCount(point, aIs4Dimensional);

      if (IsActive(point))
      {
        if (count != 2 && count != 3)
          pointsToCheck[point] = false;
      }
      else
      {
        if (count == 3)
          pointsToCheck[point] = true;
      }
    }

    points = pointsToCheck;
  }

  int count = 0;
  for (const auto & [_, state] : points)
  {
    if (state == true)
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
