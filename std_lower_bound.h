// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms.
// SPDX-License-Identifier: MIT

#pragma once

#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt std_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto len = last - first;
   while (len > 0) {
      auto half = len / 2;
      if (comp(first[half], value)) {
         first += half + 1;
         len -= half + 1;
      } else {
         len = half;
      }
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt std_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return std_lower_bound(first, last, value, std::less<>{});
}
