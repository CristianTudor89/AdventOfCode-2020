#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void PartOne();
void PartTwo();

unordered_map<int, string> messageMap;

vector<string> receivedMessages;

int main()
{
  PartTwo();

  return 0;
}

vector<vector<int>> GetSubRules(const string & aSubRules)
{
  size_t pos = aSubRules.find('|');
  if (pos != string::npos)
  {
    string subRules1 = aSubRules.substr(0, pos - 1);
    string subRules2 = aSubRules.substr(pos + 2);

    auto subRules1Vec = GetSubRules(subRules1);
    auto subRules2Vec = GetSubRules(subRules2);

    subRules1Vec.insert(subRules1Vec.end(), subRules2Vec.begin(), subRules2Vec.end());

    return subRules1Vec;
  }
  else
  {
    auto        tokens = TokenizeString(aSubRules);
    vector<int> subRules;

    for (auto & token : tokens)
      subRules.push_back(stoi(token));

    return { subRules };
  }
}

vector<string> GetMessages(const vector<int> & aRules)
{
  vector<string> rules;
  rules.push_back("");

  for (int rule : aRules)
  {
    string subRules = messageMap[rule];
    if (subRules[0] == '\"')
    {
      for (string & str : rules)
        str += subRules.substr(1, subRules.size() - 2);
    }
    else
    {
      vector<string> newRules;

      vector<vector<int>> subRulesVec = GetSubRules(subRules);

      for (const auto & subRules1 : subRulesVec)
      {
        auto messages = GetMessages(subRules1);

        for (auto & message : messages)
        {
          for (auto & str : rules)
          {
            newRules.push_back(str + message);
          }
        }
      }

      rules = newRules;
    }
  }

  return rules;
}

string GetMessageRegex(const vector<int> & aRules)
{
  string messageRegex;

  for (int rule : aRules)
  {
    string subRules = messageMap[rule];
    if (subRules[0] == '\"')
    {
      messageRegex += subRules.substr(1, subRules.size() - 2);
    }
    else
    {
      vector<vector<int>> subRulesVec = GetSubRules(subRules);

      if (subRulesVec.size() == 1)
      {
        messageRegex += GetMessageRegex(subRulesVec[0]);
      }
      else
      {
        messageRegex += "(";

        for (int i = 0; i < subRulesVec.size(); i++)
        {
          messageRegex += GetMessageRegex(subRulesVec[i]);

          if (i < subRulesVec.size() - 1)
            messageRegex += "|";
        }

        messageRegex += ")";
      }
    }
  }

  return messageRegex;
}

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto lines = reader.ReadStrings();
  int  pos   = 0;

  for (int i = 0; i < lines.size(); i++)
  {
    if (lines[i].empty())
    {
      pos = i;
      break;
    }

    auto   tokens   = TokenizeString(lines[i], ": ");
    int    rule     = stoi(tokens[0]);
    string subRules = tokens[1];

    messageMap[rule] = subRules;
  }

  for (int i = pos + 1; i < lines.size(); i++)
  {
    receivedMessages.push_back(lines[i]);
  }

  vector<string> messages = GetMessages({ 0 });

  int count = 0;
  for (auto & receivedMessage : receivedMessages)
  {
    for (auto & message : messages)
    {
      if (receivedMessage == message)
      {
        count++;
        break;
      }
    }
  }

  cout << count;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto lines = reader.ReadStrings();
  int  pos   = 0;

  for (int i = 0; i < lines.size(); i++)
  {
    if (lines[i].empty())
    {
      pos = i;
      break;
    }

    auto   tokens   = TokenizeString(lines[i], ": ");
    int    rule     = stoi(tokens[0]);
    string subRules = tokens[1];

    messageMap[rule] = subRules;
  }

  for (int i = pos + 1; i < lines.size(); i++)
  {
    receivedMessages.push_back(lines[i]);
  }

  string regexStr = GetMessageRegex({ 42 }) + "+(";

  for (int i = 1; i <= 4; i++)
  {
    string count = '{' + std::to_string(i) + '}';
    regexStr += '(' + GetMessageRegex({ 42 }) + count + GetMessageRegex({ 31 }) + count + ')';
    if (i < 4)
      regexStr += '|';
    else
      regexStr += ')';
  }

  regex messageRegex(regexStr);

  auto count = std::count_if(receivedMessages.begin(), receivedMessages.end(),
                             [&messageRegex](auto & aReceivedMessage) {
                               return regex_match(aReceivedMessage, messageRegex);
                             });

  cout << count;
}
