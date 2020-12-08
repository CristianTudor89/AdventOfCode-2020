#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;

void PartOne();
void PartTwo();

struct Instruction
{
  string name;
  int    value;
  int    index;
};

vector<Instruction> instructions;

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
  for (size_t i = 0; i < lines.size(); i++)
  {
    auto tokens = TokenizeString(lines[i], " ");

    instructions.push_back({ tokens[0], stoi(tokens[1]), (int)i });
  }

  vector<int> indices;
  int         pos = 0, acc = 0;

  while (true)
  {
    auto & instr = instructions[pos];

    bool found = any_of(indices.begin(), indices.end(), [pos](int index) {
      return index == pos;
    });
    if (found)
      break;

    indices.push_back(pos);

    if (instr.name == "jmp")
    {
      pos += instr.value;
    }
    else if (instr.name == "acc")
    {
      pos++;
      acc += instr.value;
    }
    else if (instr.name == "nop")
    {
      pos++;
    }
  }

  cout << acc;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto lines = reader.ReadStrings();
  for (size_t i = 0; i < lines.size(); i++)
  {
    auto tokens = TokenizeString(lines[i], " ");

    instructions.push_back({ tokens[0], stoi(tokens[1]), (int)i });
  }

  auto origInstr{ instructions };

  for (size_t i = 0; i < instructions.size(); i++)
  {
    instructions = origInstr;

    if (instructions[i].name == "nop")
      instructions[i].name = "jmp";
    else if (instructions[i].name == "jmp")
      instructions[i].name = "nop";

    vector<int> indices;
    int         pos = 0, acc = 0;

    while (true)
    {
      if (pos == instructions.size())
      {
        cout << acc;
        break;
      }

      auto & instr = instructions[pos];

      bool found = any_of(indices.begin(), indices.end(), [pos](int index) {
        return index == pos;
      });
      if (found)
        break;

      indices.push_back(pos);

      if (instr.name == "jmp")
      {
        pos += instr.value;
      }
      else if (instr.name == "acc")
      {
        pos++;
        acc += instr.value;
      }
      else if (instr.name == "nop")
      {
        pos++;
      }
    }
  }
}
