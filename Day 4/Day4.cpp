#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;

struct Passport
{
  string byr;
  string iyr;
  string eyr;
  string hgt;
  string hcl;
  string ecl;
  string pid;
  string cid;

  void reset() { byr = iyr = eyr = hgt = hcl = ecl = pid = cid = ""; }

  bool isValid()
  {
    if (byr.empty())
      return false;

    int byr1 = stoi(byr);
    if (byr1 < 1920 || byr1 > 2002)
      return false;

    if (iyr.empty())
      return false;

    int iyr1 = stoi(iyr);
    if (iyr1 < 2010 || iyr1 > 2020)
      return false;

    if (eyr.empty())
      return false;

    int eyr1 = stoi(eyr);
    if (eyr1 < 2020 || eyr1 > 2030)
      return false;

    if (hgt.size() < 4)
      return false;

    int hgt1 = stoi(hgt.substr(0, hgt.size() - 2));
    if (hgt.substr(hgt.size() - 2) == "cm" && (hgt1 < 150 || hgt1 > 193))
      return false;

    if (hgt.substr(hgt.size() - 2) == "in" && (hgt1 < 59 || hgt1 > 76))
      return false;

    if (hcl.size() != 7)
      return false;

    if (hcl[0] != '#')
      return false;

    for (int i = 1; i <= 6; i++)
      if (hcl[i] < '0' && hcl[i] > '9' && hcl[i] < 'a' && hcl[i] > 'f')
        return false;

    if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" &&
        ecl != "hzl" && ecl != "oth")
      return false;

    if (pid.size() != 9)
      return false;

    for (int i = 0; i < pid.size(); i++)
      if (pid[i] < '0' && pid[i] > '9')
        return false;

    return true;
  }
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

  auto     values = reader.ReadStrings();
  int      count  = 0;
  Passport pass;

  for (const auto & value : values)
  {
    if (value.empty())
    {
      if (!(pass.byr.empty() || pass.iyr.empty() || pass.eyr.empty() || pass.hgt.empty() ||
            pass.hcl.empty() || pass.ecl.empty() || pass.pid.empty()))
        count++;

      pass.reset();
      continue;
    }

    auto v = TokenizeString(value, " ");
    for (const auto & p : v)
    {
      auto pair = TokenizeString(p, ":");

      if (pair[0] == "byr")
        pass.byr = pair[1];
      else if (pair[0] == "iyr")
        pass.iyr = pair[1];
      else if (pair[0] == "eyr")
        pass.eyr = pair[1];
      else if (pair[0] == "hgt")
        pass.hgt = pair[1];
      else if (pair[0] == "hcl")
        pass.hcl = pair[1];
      else if (pair[0] == "ecl")
        pass.ecl = pair[1];
      else if (pair[0] == "pid")
        pass.pid = pair[1];
      else if (pair[0] == "cid")
        pass.cid = pair[1];
    }
  }

  if (!(pass.byr.empty() || pass.iyr.empty() || pass.eyr.empty() || pass.hgt.empty() ||
        pass.hcl.empty() || pass.ecl.empty() || pass.pid.empty()))
    count++;

  cout << count;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto     values = reader.ReadStrings();
  int      count  = 0;
  Passport pass;

  for (const auto & value : values)
  {
    if (value.empty())
    {
      if (pass.isValid())
        count++;

      pass.reset();
      continue;
    }

    auto v = TokenizeString(value, " ");
    for (const auto & p : v)
    {
      auto pair = TokenizeString(p, ":");

      if (pair[0] == "byr")
        pass.byr = pair[1];
      else if (pair[0] == "iyr")
        pass.iyr = pair[1];
      else if (pair[0] == "eyr")
        pass.eyr = pair[1];
      else if (pair[0] == "hgt")
        pass.hgt = pair[1];
      else if (pair[0] == "hcl")
        pass.hcl = pair[1];
      else if (pair[0] == "ecl")
        pass.ecl = pair[1];
      else if (pair[0] == "pid")
        pass.pid = pair[1];
      else if (pair[0] == "cid")
        pass.cid = pair[1];
    }
  }

  if (!(pass.byr.empty() || pass.iyr.empty() || pass.eyr.empty() || pass.hgt.empty() ||
        pass.hcl.empty() || pass.ecl.empty() || pass.pid.empty()))
    count++;

  cout << count;
}
