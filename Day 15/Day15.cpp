#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

struct History
{
  int previous{ -1 };
  int last{ -1 };
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

  auto numbers = reader.ReadValues(",");
  int  turn    = numbers.size();

  while (turn != 2020)
  {
    int lastNumber = numbers[turn - 1];

    auto it = std::find(numbers.rbegin() + 1, numbers.rend(), lastNumber);
    if (it == numbers.rend())
    {
      numbers.push_back(0);
    }
    else
    {
      int diff = turn - (numbers.rend() - it);
      numbers.push_back(diff);
    }

    turn++;
  }

  cout << numbers.back() << endl;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto numbers = reader.ReadValues(",");
  int  turn    = numbers.size();

  unordered_map<int, History> numberMap;
  for (int i = 0; i < numbers.size(); i++)
    numberMap[numbers[i]] = { -1, i + 1 };

  while (turn != 30000000)
  {
    int lastNumber = numbers[turn - 1];

    auto it = numberMap.find(lastNumber);
    if (it != numberMap.end())
    {
      turn++;

      if (numberMap[lastNumber].previous == -1)
      {
        numbers.push_back(0);

        numberMap[0].previous = numberMap[0].last;
        numberMap[0].last     = turn;
      }
      else
      {
        int diff = numberMap[lastNumber].last - numberMap[lastNumber].previous;
        numbers.push_back(diff);

        numberMap[diff].previous = numberMap[diff].last;
        numberMap[diff].last     = turn;
      }
    }
  }

  cout << numbers.back() << endl;
}
