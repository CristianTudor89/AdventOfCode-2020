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
};  // namespace Algorithm
