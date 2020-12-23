#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void PartOne();
void PartTwo();

int main()
{
  PartTwo();

  return 0;
}

list<int>::iterator GetNextCup(list<int> & aCups, list<int>::iterator it)
{
  it++;
  if (it == aCups.end())
    it = aCups.begin();

  return it;
}

vector<list<int>::iterator> GetNextThreeCups(list<int> & aCups, list<int>::iterator it)
{
  vector<list<int>::iterator> nextThreeCups;

  for (int i = 0; i < 3; i++)
  {
    it = GetNextCup(aCups, it);
    nextThreeCups.push_back(it);
  }

  return nextThreeCups;
}

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto   values   = reader.ReadStrings();
  string labeling = values[0];

  list<int> cups;
  for (int i = 0; i < labeling.size(); i++)
    cups.push_back(labeling[i] - 48);

  int minValue = 1;
  int maxValue = cups.size();

  int  currentMove = 1;
  auto currentCup  = cups.begin();

  while (currentMove <= 100)
  {
    vector<int> removedCups;

    auto nextThreeCups = GetNextThreeCups(cups, currentCup);
    for (auto cup : nextThreeCups)
    {
      removedCups.push_back(*cup);
      cups.erase(cup);
    }

    int dest = *currentCup - 1;
    if (dest == minValue - 1)
      dest = maxValue;

    while (Contains(removedCups, dest))
    {
      dest--;

      if (dest < minValue)
        dest = maxValue;
    }

    auto destIt = cups.begin();
    while (*destIt != dest)
      destIt = GetNextCup(cups, destIt);

    destIt++;

    for (int i = 0; i < 3; i++)
      cups.insert(destIt, removedCups[i]);

    currentCup = GetNextCup(cups, currentCup);

    currentMove++;
  }

  auto it = cups.begin();
  while (it != cups.end() && *it != minValue)
    it++;

  it++;
  for (int i = 0; i < cups.size() - 1; i++)
  {
    cout << *it;
    it = GetNextCup(cups, it);
  }
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto   values   = reader.ReadStrings();
  string labeling = values[0];

  list<int>                   cups;
  vector<list<int>::iterator> iterators(1000010, cups.end());

  for (int i = 1; i <= 9; i++)
  {
    int val = labeling[i - 1] - 48;
    cups.push_back(val);
    iterators[val + 1] = --cups.end();
  }

  for (int i = 10; i <= 1000000; i++)
  {
    cups.push_back(i);
    iterators[i + 1] = --cups.end();
  }

  int minValue = 1;
  int maxValue = cups.size();

  int  currentMove = 1;
  auto currentCup  = cups.begin();

  while (currentMove <= 10000000)
  {
    vector<int> removedCups;

    auto nextThreeCups = GetNextThreeCups(cups, currentCup);
    for (auto cup : nextThreeCups)
    {
      removedCups.push_back(*cup);
      cups.erase(cup);
    }

    int dest = *currentCup - 1;
    if (dest == minValue - 1)
      dest = maxValue;

    while (Contains(removedCups, dest))
    {
      dest--;

      if (dest < minValue)
        dest = maxValue;
    }

    auto destIt = iterators[dest + 1];

    for (int i = 2; i >= 0; i--)
    {
      auto it = cups.insert(GetNextCup(cups, destIt), removedCups[i]);

      iterators[removedCups[i] + 1] = it;
    }

    currentCup = GetNextCup(cups, currentCup);

    currentMove++;
  }

  auto it = find(cups.begin(), cups.end(), 1);

  auto it1 = GetNextCup(cups, it);
  auto it2 = GetNextCup(cups, it1);

  long long product = (long long)*it1 * (long long)*it2;

  cout << product;
}
