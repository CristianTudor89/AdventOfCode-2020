#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void Solution(bool aPartTwo);
void PartOne();
void PartTwo();

int main()
{
  PartTwo();

  return 0;
}

void Solution(bool aPartTwo)
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto lines = reader.ReadStrings();

  unordered_map<string, vector<vector<string>>> allergensIngredientsMap;

  unordered_set<string>      allIngredients;
  unordered_map<string, int> occurrenceCount;

  for (auto & line : lines)
  {
    auto values      = TokenizeString(line, " (");
    auto ingredients = TokenizeString(values[0]);

    for (auto & ingr : ingredients)
    {
      allIngredients.insert(ingr);
      occurrenceCount[ingr]++;
    }

    auto allergensStr = values[1].substr(9);
    allergensStr.pop_back();

    auto allergens = TokenizeString(allergensStr, ", ");
    for (auto & allergen : allergens)
      allergensIngredientsMap[allergen].push_back(ingredients);
  }

  unordered_map<string, vector<string>> allergensCommonIngredientsMap;

  for (auto & [allergen, possibleIngredients] : allergensIngredientsMap)
  {
    unordered_map<string, int> ingredientCountMap;

    for (auto & ingredients : possibleIngredients)
    {
      for (auto & ingredient : ingredients)
        ingredientCountMap[ingredient]++;
    }

    vector<string> commonIngredients;

    for (auto & [ingredient, count] : ingredientCountMap)
    {
      if (count == allergensIngredientsMap[allergen].size())
        commonIngredients.push_back(ingredient);
    }

    allergensCommonIngredientsMap[allergen] = commonIngredients;
  }

  if (!aPartTwo)
  {
    vector<string> missingIngr;
    for (auto & ingredient : allIngredients)
    {
      bool found = true;
      for (auto & [allergen, ingredients] : allergensCommonIngredientsMap)
      {
        if (Contains(ingredients, ingredient))
          found = false;
      }

      if (found)
        missingIngr.push_back(ingredient);
    }

    int count = 0;
    for (auto & ingr : missingIngr)
    {
      for (auto & [ingredient, occCount] : occurrenceCount)
      {
        if (ingr == ingredient)
          count += occCount;
      }
    }

    cout << count;
  }
  else
  {
    map<string, string> allergenIngrMap;

    while (!allergensCommonIngredientsMap.empty())
    {
      int    min = 10000;
      string allergen;

      for (auto & [allergen1, ingredients] : allergensCommonIngredientsMap)
      {
        if (ingredients.size() < min)
        {
          min      = ingredients.size();
          allergen = allergen1;
        }
      }

      auto & ingredients = allergensCommonIngredientsMap[allergen];
      assert(ingredients.size() == 1);

      string foundIngr = ingredients[0];

      allergenIngrMap[allergen] = foundIngr;

      allergensCommonIngredientsMap.erase(allergen);

      for (auto & [allergen1, ingredients1] : allergensCommonIngredientsMap)
      {
        if (Contains(ingredients1, foundIngr))
          ingredients1.erase(std::find(ingredients1.begin(), ingredients1.end(), foundIngr));
      }
    }

    string ingredientList;
    for (auto & [allergen, ingr] : allergenIngrMap)
      ingredientList += ingr + ",";

    ingredientList.pop_back();
    cout << ingredientList;
  }
}

void PartOne()
{
  Solution(false);
}

void PartTwo()
{
  Solution(true);
}
