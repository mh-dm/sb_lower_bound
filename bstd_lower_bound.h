// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms
// SPDX-License-Identifier: MIT

#pragma once

#include "unpredictable.h"

#include <functional>
#include <iostream>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt bstd_lower_bound(
      ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = last - first;
   while (length > 0) {
      auto half = length / 2;
      bool compare = __builtin_unpredictable(comp(first[half], value));
      first = compare ? first + half + 1 : first;
      length = compare ? length - half - 1 : half;
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt bstd_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return bstd_lower_bound(first, last, value, std::less<>{});
}
