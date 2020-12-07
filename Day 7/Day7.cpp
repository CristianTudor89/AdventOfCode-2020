#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;

struct Bag
{
  string type;
  int    amount;
};

unordered_map<string, vector<Bag>> bagsMap;

void PartOne();
void PartTwo();

void CountTypes(const string & bagName, unordered_set<string> & bagTypes)
{
  for (const auto & bag : bagsMap[bagName])
  {
    bagTypes.insert(bag.type);

    CountTypes(bag.type, bagTypes);
  }
}

int Count1(const string & bagName)
{
  int count = 0;

  auto & bags = bagsMap[bagName];

  for (const auto & bag : bags)
  {
    auto & bags1 = bagsMap[bag.type];
    if (bags1.size() == 1 && bagsMap.find(bags1[0].type) == bagsMap.end())
      count += bag.amount + bag.amount * bags1[0].amount;
    else
      count += bag.amount + bag.amount * Count1(bag.type);
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

  auto lines = reader.ReadStrings();

  for (const auto & line : lines)
  {
    auto tokens = TokenizeString(line, " contain ");

    string outerBagName;
    auto   outerBagTokens = TokenizeString(tokens[0], " ");
    for (size_t i = 0; i < outerBagTokens.size() - 1; i++)
      outerBagName += outerBagTokens[i];

    auto bagTokens = TokenizeString(tokens[1], ", ");

    for (size_t i = 0; i < bagTokens.size(); i++)
    {
      // get rid of '.'
      if (i == bagTokens.size() - 1)
        bagTokens[i].pop_back();

      string innerBagName;
      auto   innerBagTokens = TokenizeString(bagTokens[i], " ");
      for (size_t j = 1; j < innerBagTokens.size() - 1; j++)
        innerBagName += innerBagTokens[j];

      if (innerBagTokens[0] != "no")
      {
        int amount = stoi(innerBagTokens[0]);
        bagsMap[innerBagName].push_back({ outerBagName, amount });
      }
    }
  }

  unordered_set<string> bagTypes;
  CountTypes("shinygold", bagTypes);

  cout << bagTypes.size();
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto lines = reader.ReadStrings();

  for (const auto & line : lines)
  {
    auto tokens = TokenizeString(line, " contain ");

    string outerBagName;
    auto   outerBagTokens = TokenizeString(tokens[0], " ");
    for (size_t i = 0; i < outerBagTokens.size() - 1; i++)
      outerBagName += outerBagTokens[i];

    auto bagTokens = TokenizeString(tokens[1], ", ");

    for (size_t i = 0; i < bagTokens.size(); i++)
    {
      // get rid of '.'
      if (i == bagTokens.size() - 1)
        bagTokens[i].pop_back();

      string innerBagName;
      auto   innerBagTokens = TokenizeString(bagTokens[i], " ");
      for (size_t j = 1; j < innerBagTokens.size() - 1; j++)
        innerBagName += innerBagTokens[j];

      if (innerBagTokens[0] != "no")
      {
        int amount = stoi(innerBagTokens[0]);
        bagsMap[outerBagName].push_back({ innerBagName, amount });
      }
    }
  }

  set<string> bags;
  int         count = Count1("shinygold");

  cout << count;
}
