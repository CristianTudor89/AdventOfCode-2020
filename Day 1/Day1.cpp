#include "Input.h"

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

  auto values = reader.ReadValues();
  for (size_t i = 0; i < values.size() - 1; i++)
    for (size_t j = i + 1; j < values.size(); j++)
      if (values[i] + values[j] == 2020)
        cout << values[i] * values[j] << endl;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto values = reader.ReadValues();

  for (size_t i = 0; i < values.size() - 2; i++)
    for (size_t j = i + 1; j < values.size() - 1; j++)
      for (size_t k = j + 1; k < values.size(); k++)
        if (values[i] + values[j] + values[k] == 2020)
          cout << values[i] * values[j] * values[k] << endl;
}
