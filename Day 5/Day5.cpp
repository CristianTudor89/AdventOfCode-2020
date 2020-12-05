#include "Input.h"
#include "StringUtil.h"
#include <algorithm>

using namespace StringUtil;

void UpdateRange(int & low, int & high, char c)
{
  if (c == 'F' || c == 'L')
    high = low + (high - low) / 2;
  else
    low = low + (high - low) / 2 + 1;
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

  vector<int> seatIds;

  auto values = reader.ReadValues<string>();
  for (const auto & value : values)
  {
    int rowMin = 0, rowMax = 127, colMin = 0, colMax = 7;

    for (int i = 0; i < 7; i++)
      UpdateRange(rowMin, rowMax, value[i]);

    for (int i = 7; i < 10; i++)
      UpdateRange(colMin, colMax, value[i]);

    seatIds.push_back(rowMin * 8 + colMin);
  }

  auto maxValue = *max_element(seatIds.begin(), seatIds.end());

  cout << maxValue;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  vector<int> seatIds;

  auto values = reader.ReadValues<string>();
  for (const auto & value : values)
  {
    int rowMin = 0, rowMax = 127, colMin = 0, colMax = 7;

    for (int i = 0; i < 7; i++)
      UpdateRange(rowMin, rowMax, value[i]);

    for (int i = 7; i < 10; i++)
      UpdateRange(colMin, colMax, value[i]);

    seatIds.push_back(rowMin * 8 + colMin);
  }

  auto minValue = *min_element(seatIds.begin(), seatIds.end());
  auto maxValue = *max_element(seatIds.begin(), seatIds.end());

  for (int i = minValue; i <= maxValue; i++)
  {
    auto it = find(seatIds.begin(), seatIds.end(), i);
    if (it == seatIds.end())
      cout << i << endl;
  }
}
