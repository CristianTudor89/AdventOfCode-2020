#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

struct Point
{
  Point(int aX, int aY)
    : x(aX)
    , y(aY)
  {
  }

  void Move(const string & aAction)
  {
    char action = aAction[0];
    int  amount = stoi(aAction.substr(1));

    if (action == 'N')
    {
      y += amount;
    }
    else if (action == 'S')
    {
      y -= amount;
    }
    else if (action == 'E')
    {
      x += amount;
    }
    else if (action == 'W')
    {
      x -= amount;
    }
    else if (action == 'L' || action == 'R')
    {
      for (int i = 0; i < amount / 90; i++)
        UpdateDir(action);
    }
    else if (action == 'F')
    {
      string forwardAction{ dir };
      forwardAction += std::to_string(amount);

      Move(forwardAction);
    }
  }

  void UpdateDir(char aTurn)
  {
    vector<char> dirs{ 'N', 'E', 'S', 'W' };
    int          index = 0;

    for (int i = 0; i < 4; i++)
    {
      if (dir == dirs[i])
      {
        index = i;
        break;
      }
    }

    if (aTurn == 'L')
    {
      dir = dirs[index > 0 ? index - 1 : 3];
    }
    else if (aTurn == 'R')
    {
      dir = dirs[index < 3 ? index + 1 : 0];
    }
  }

  char dir{ 'E' };
  int  x{ 0 };
  int  y{ 0 };
};

struct ShipWaypoint
{
  ShipWaypoint(int aShipX, int aShipY, int aWaypointX, int aWaypointY)
    : shipX(aShipX)
    , shipY(aShipY)
    , waypointX(aWaypointX)
    , waypointY(aWaypointY)
  {
  }

  void Move(const string & aAction, bool aMoveShip = false)
  {
    char action = aAction[0];
    int  amount = stoi(aAction.substr(1));

    if (action == 'N')
    {
      if (aMoveShip)
        shipY += amount;
      else
        waypointY += amount;
    }
    else if (action == 'S')
    {
      if (aMoveShip)
        shipY -= amount;
      else
        waypointY -= amount;
    }
    else if (action == 'E')
    {
      if (aMoveShip)
        shipX += amount;
      else
        waypointX += amount;
    }
    else if (action == 'W')
    {
      if (aMoveShip)
        shipX -= amount;
      else
        waypointX -= amount;
    }
    else if (action == 'L' || action == 'R')
    {
      for (int i = 0; i < amount / 90; i++)
      {
        int newWaypointX = 0, newWaypointY = 0;

        for (char dir : { 'E', 'N' })
          UpdateWaypoint(action, dir, newWaypointX, newWaypointY);

        waypointX = newWaypointX;
        waypointY = newWaypointY;
      }
    }
    else if (action == 'F')
    {
      string forwardAction{ 'E' };
      forwardAction += std::to_string(amount * waypointX);

      Move(forwardAction, true);

      forwardAction = { 'N' };
      forwardAction += std::to_string(amount * waypointY);

      Move(forwardAction, true);
    }
  }

  void UpdateWaypoint(char aTurn, char aDir, int & aNewWaypointX, int & aNewWaypointY)
  {
    if (aTurn == 'L')
    {
      if (aDir == 'N')
      {
        aNewWaypointX = -waypointY;
      }
      else if (aDir == 'E')
      {
        aNewWaypointY = waypointX;
      }
    }
    else if (aTurn == 'R')
    {
      if (aDir == 'N')
      {
        aNewWaypointX = waypointY;
      }
      else if (aDir == 'E')
      {
        aNewWaypointY = -waypointX;
      }
    }
  }

  int shipX{ 0 };
  int shipY{ 0 };
  int waypointX{ 0 };
  int waypointY{ 0 };
};

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

  auto actions = reader.ReadStrings();

  Point pos(0, 0);

  for (const auto & action : actions)
  {
    pos.Move(action);
  }

  cout << abs(pos.x) + abs(pos.y);
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto actions = reader.ReadStrings();

  ShipWaypoint shipWaypoint(0, 0, 10, 1);

  for (auto & action : actions)
  {
    shipWaypoint.Move(action);
  }

  cout << abs(shipWaypoint.shipX) + abs(shipWaypoint.shipY);
}
