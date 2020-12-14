#pragma once

#include "stdafx.h"

namespace Algorithm
{
template <class Container, class T>
bool Contains(const Container & aContainer, const T & aValue)
{
  auto beginIt = begin(aContainer);
  auto endIt   = end(aContainer);

  return find(beginIt, endIt, aValue) != endIt;
}

template <class T>
void InsertOrUpdate(vector<pair<T, T>> & aContainer, const T & aKey, const T & aValue)
{
  auto it = std::find_if(aContainer.begin(), aContainer.end(), [&aKey](const auto & aKeyValuePair) {
    return aKeyValuePair.first == aKey;
  });

  if (it != aContainer.end())
    it->second = aValue;
  else
    aContainer.push_back({ aKey, aValue });
}

};  // namespace Algorithm
