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

bool Match(const vector<int> & aTickets, const vector<pair<int, int>> & aRanges)
{
  if (aTickets.empty())
    return false;

  for (int ticket : aTickets)
  {
    bool found = false;
    for (const auto & range : aRanges)
    {
      if (ticket >= range.first && ticket <= range.second)
        found = true;
    }

    if (!found)
      return false;
  }

  return true;
}

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto                   strings = reader.ReadStrings();
  vector<pair<int, int>> ranges;

  for (const auto & str : strings)
  {
    if (str.empty())
      break;

    auto tokens    = TokenizeString(str, ": ");
    auto newTokens = TokenizeString(tokens[1], " or ");

    for (int i : { 0, 1 })
      ranges.push_back(GetBounds(newTokens[i]));
  }

  int pos = 0;
  for (int i = 0; i < strings.size(); i++)
  {
    if (strings[i] == "nearby tickets:")
    {
      pos = i;
      break;
    }
  }

  int sum = 0;
  for (int i = pos + 1; i < strings.size(); i++)
  {
    auto values = TokenizeString(strings[i], ",");
    for (const auto & val : values)
    {
      int  intVal       = stoi(val);
      bool foundInvalid = true;

      for (const auto & range : ranges)
      {
        if (intVal >= range.first && intVal <= range.second)
        {
          foundInvalid = false;
          break;
        }
      }

      if (foundInvalid)
        sum += intVal;
    }
  }

  cout << sum;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto strings = reader.ReadStrings();

  vector<pair<int, int>>                        rangesInvalid;
  unordered_map<string, vector<pair<int, int>>> ranges;

  for (const auto & str : strings)
  {
    if (str.empty())
      break;

    auto tokens    = TokenizeString(str, ": ");
    auto newTokens = TokenizeString(tokens[1], " or ");

    for (int i : { 0, 1 })
    {
      ranges[tokens[0]].push_back(GetBounds(newTokens[i]));
      rangesInvalid.push_back(GetBounds(newTokens[i]));
    }
  }

  int pos = 0;
  for (int i = 0; i < strings.size(); i++)
  {
    if (strings[i] == "nearby tickets:")
    {
      pos = i;
      break;
    }
  }

  vector<vector<int>> nearbyTickets;

  for (int i = pos + 1; i < strings.size(); i++)
  {
    auto        values = TokenizeString(strings[i], ",");
    vector<int> tickets;

    for (const auto & val : values)
    {
      int  intVal       = stoi(val);
      bool foundInvalid = true;

      for (const auto & range : rangesInvalid)
      {
        if (intVal >= range.first && intVal <= range.second)
        {
          foundInvalid = false;
          break;
        }
      }

      if (!foundInvalid)
        tickets.push_back(intVal);
    }

    nearbyTickets.push_back(tickets);
  }

  for (int i = 0; i < strings.size(); i++)
  {
    if (strings[i] == "your ticket:")
    {
      pos = i;
      break;
    }
  }

  vector<int> yourTickets;
  auto        yourTicketsVals = TokenizeString(strings[pos + 1], ",");
  for (const auto & val : yourTicketsVals)
    yourTickets.push_back(stoi(val));

  vector<vector<string>> ticketNames;

  int column = 0;

  while (true)
  {
    vector<int> columnValues;

    for (const auto & nearbyTicket : nearbyTickets)
    {
      if (column < nearbyTicket.size())
        columnValues.push_back(nearbyTicket[column]);
    }

    int length = ticketNames.size();

    for (const auto & range : ranges)
    {
      bool found = Match(columnValues, range.second);
      if (found)
      {
        if (column < ticketNames.size() && !Contains(ticketNames[column], range.first))
          ticketNames[column].push_back(range.first);
        else
          ticketNames.push_back({ range.first });
      }
    }

    if (ticketNames.size() == length)
      break;

    column++;
  }

  unordered_map<int, string> ticketsMap;

  while (!ticketNames.empty())
  {
    int posMin = 0, min = 100;

    for (int i = 0; i < ticketNames.size(); i++)
    {
      int count = std::count_if(ticketNames[i].begin(), ticketNames[i].end(), [](string & val) {
        return !val.empty();
      });
      if (count < min && count != 0)
      {
        min    = count;
        posMin = i;
      }
    }

    int index = 0;
    while (index < ticketNames[posMin].size() && ticketNames[posMin][index].empty())
      index++;

    if (index == ticketNames[posMin].size())
      break;

    string valueToClear = ticketNames[posMin][index];

    ticketsMap[posMin] = valueToClear;

    for (int i = 0; i < ticketNames.size(); i++)
    {
      if (Contains(ticketNames[i], valueToClear))
      {
        auto it = std::find(ticketNames[i].begin(), ticketNames[i].end(), valueToClear);
        it->clear();
      }
    }
  }

  int       count = 0;
  long long prod  = 1;

  for (const auto & [pos, name] : ticketsMap)
  {
    if (name.substr(0, 9) == "departure")
    {
      count++;
      prod *= yourTickets[pos];

      if (count == 6)
        break;
    }
  }

  cout << prod;
}
