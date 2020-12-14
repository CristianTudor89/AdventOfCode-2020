#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void ComputeAddresses(vector<string> & aAddresses, vector<string> & aFinalAddresses)
{
  vector<string> newAddresses;

  for (auto & address : aAddresses)
  {
    for (int i = 0; i < address.size(); i++)
    {
      if (address[i] == 'X')
      {
        address[i] = '0';
        newAddresses.push_back(address);

        address[i] = '1';
        newAddresses.push_back(address);

        break;
      }
    }
  }

  if (newAddresses.empty())
    aFinalAddresses = aAddresses;
  else
    ComputeAddresses(newAddresses, aFinalAddresses);
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

  auto                          strings = reader.ReadStrings();
  unordered_map<int, long long> valueResultMap;
  unordered_map<int, long long> valueResultPerMaskMap;
  string                        mask;

  for (const auto & str : strings)
  {
    auto tokens = TokenizeString(str, " = ");

    if (str.empty() || tokens[0] == "mask")
    {
      for (const auto & [value, result] : valueResultPerMaskMap)
      {
        string valueStr  = std::bitset<36>(value).to_string();
        string resultStr = std::bitset<36>(result).to_string();

        for (int i = 0; i < 36; i++)
        {
          if (mask[i] != 'X')
            resultStr[i] = mask[i];
        }

        long long newResult = std::bitset<36>(resultStr).to_ullong();

        valueResultMap[value] = newResult;
      }

      if (tokens[0] == "mask")
      {
        mask                  = tokens[1];
        valueResultPerMaskMap = {};
      }
    }
    else
    {
      auto valueResultTokens = TokenizeString(tokens[0], "[");
      valueResultTokens[1].pop_back();

      int value  = stoi(valueResultTokens[1]);
      int result = stoi(tokens[1]);

      valueResultPerMaskMap[value] = result;
    }
  }

  long long sum = 0;
  for (const auto & [value, result] : valueResultMap)
  {
    sum += result;
  }

  cout << sum;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto                               strings = reader.ReadStrings();
  vector<pair<long long, long long>> addressResultPairs;
  vector<pair<long long, long long>> addressResultPerMaskPairs;
  string                             mask;

  for (const auto & str : strings)
  {
    auto tokens = TokenizeString(str, " = ");

    if (str.empty() || tokens[0] == "mask")
    {
      for (auto & [address, result] : addressResultPerMaskPairs)
      {
        string addressStr = std::bitset<36>(address).to_string();

        for (int i = 0; i < 36; i++)
        {
          if (mask[i] == '1' || mask[i] == 'X')
            addressStr[i] = mask[i];
        }

        vector<string> addresses(1, addressStr), finalAddresses;

        ComputeAddresses(addresses, finalAddresses);

        for (const auto & finalAddress : finalAddresses)
        {
          long long addressVal = std::bitset<36>(finalAddress).to_ullong();

          InsertOrUpdate(addressResultPairs, addressVal, result);
        }
      }

      if (tokens[0] == "mask")
      {
        mask                      = tokens[1];
        addressResultPerMaskPairs = {};
      }
    }
    else
    {
      auto addressResultTokens = TokenizeString(tokens[0], "[");
      addressResultTokens[1].pop_back();

      long long address = stoi(addressResultTokens[1]);
      long long result  = stoi(tokens[1]);

      InsertOrUpdate(addressResultPerMaskPairs, address, result);
    }
  }

  long long sum = 0;
  for (const auto & [address, result] : addressResultPairs)
  {
    sum += result;
  }

  cout << sum;
}
