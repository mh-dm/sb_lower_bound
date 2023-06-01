// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms
// SPDX-License-Identifier: MIT

#pragma once

#include <functional>
#include <iostream>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt rem_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = last - first;
   while (length > 0) {
      bool rem = (length + 1) % 2;
      length /= 2;
      auto compare = comp(first[length], value);
      first = compare ? first + length + 1 : first;
      length = compare ? length - rem : length;
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt rem_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return rem_lower_bound(first, last, value, std::less<>{});
}
