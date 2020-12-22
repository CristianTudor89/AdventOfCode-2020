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

struct Config
{
  bool operator==(const Config & aConfig) const
  {
    return config1 == aConfig.config1 && config2 == aConfig.config2;
  }

  vector<int> config1;
  vector<int> config2;
};

bool RecursiveCombat(vector<int> & aPlayer1, vector<int> & aPlayer2)
{
  vector<Config> uniqueConfig;

  while (!aPlayer1.empty() && !aPlayer2.empty())
  {
    Config config{ aPlayer1, aPlayer2 };
    if (Contains(uniqueConfig, config))
      return true;

    uniqueConfig.push_back(config);

    int player1Card = aPlayer1[0];
    int player2Card = aPlayer2[0];

    aPlayer1.erase(aPlayer1.begin());
    aPlayer2.erase(aPlayer2.begin());

    bool player1Won = false;

    if (player1Card <= aPlayer1.size() && player2Card <= aPlayer2.size())
    {
      vector<int> player1Copy(player1Card);
      copy_n(aPlayer1.begin(), player1Card, player1Copy.begin());

      vector<int> player2Copy(player2Card);
      copy_n(aPlayer2.begin(), player2Card, player2Copy.begin());

      player1Won = RecursiveCombat(player1Copy, player2Copy);
    }
    else
    {
      player1Won = (player1Card > player2Card);
    }

    if (player1Won)
    {
      aPlayer1.push_back(player1Card);
      aPlayer1.push_back(player2Card);
    }
    else
    {
      aPlayer2.push_back(player2Card);
      aPlayer2.push_back(player1Card);
    }
  }

  return !aPlayer1.empty();
}

void Solution(bool aPartTwo)
{
  ifstream    input("in.txt");
  InputReader reader(input);

  vector<int> player1, player2;

  auto lines = reader.ReadStrings();
  for (int i = 0; i < lines.size(); i++)
  {
    if (lines[i] == "")
    {
      for (int j = 1; j < i; j++)
      {
        player1.push_back(stoi(lines[j]));
      }

      for (int j = i + 2; j < lines.size(); j++)
      {
        player2.push_back(stoi(lines[j]));
      }

      break;
    }
  }

  bool player1Won = false;

  if (aPartTwo)
  {
    player1Won = RecursiveCombat(player1, player2);
  }
  else
  {
    while (!player1.empty() && !player2.empty())
    {
      int player1Card = player1[0];
      int player2Card = player2[0];

      if (player1Card > player2Card)
      {
        player1.push_back(player1Card);
        player1.push_back(player2Card);
      }
      else
      {
        player2.push_back(player2Card);
        player2.push_back(player1Card);
      }

      player1.erase(player1.begin());
      player2.erase(player2.begin());
    }
  }

  int sum = 0;
  if (player1Won || !player1.empty())
  {
    for (int i = 0; i < player1.size(); i++)
    {
      sum += (player1.size() - i) * player1[i];
    }
  }
  else
  {
    for (int i = 0; i < player2.size(); i++)
    {
      sum += (player2.size() - i) * player2[i];
    }
  }

  cout << sum;
}

void PartOne()
{
  Solution(false);
}

void PartTwo()
{
  Solution(true);
}
