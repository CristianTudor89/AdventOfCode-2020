#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

int GetAdapterCount(const vector<int> & aJoltages, int aIndex)
{
  size_t count = 0;

  for (int i = 1; i <= 3; i++)
  {
    if (aIndex >= i && aJoltages[aIndex] - aJoltages[aIndex - i] <= 3)
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

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto joltages = reader.ReadValues();

  int maxJoltage = *std::max_element(joltages.begin(), joltages.end());

  joltages.push_back(0);
  joltages.push_back(maxJoltage + 3);

  std::sort(joltages.begin(), joltages.end());

  int diff1Count = 0, diff3Count = 0;

  for (size_t i = 0; i < joltages.size() - 1; i++)
  {
    if (joltages[i + 1] - joltages[i] == 1)
      diff1Count++;
    else if (joltages[i + 1] - joltages[i] == 3)
      diff3Count++;
  }

  cout << diff1Count * diff3Count;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto joltages = reader.ReadValues();

  int maxJoltage = *std::max_element(joltages.begin(), joltages.end());

  joltages.push_back(0);
  joltages.push_back(maxJoltage + 3);

  std::sort(joltages.begin(), joltages.end());

  vector<long long> sums(joltages.size());
  sums[0] = 1;

  for (size_t i = 1; i < joltages.size(); i++)
  {
    int count = GetAdapterCount(joltages, i);

    for (int j = 1; j <= count; j++)
      sums[i] += sums[i - j];
  }

  cout << sums.back();
}
