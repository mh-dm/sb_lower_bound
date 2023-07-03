// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms.
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt sb_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = last - first;
   while (length > 0) {
      auto half = length / 2;
      if (comp(first[half], value)) {
         // length - half equals half + length % 2
         first += length - half;
      }
      length = half;
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt sb_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return sb_lower_bound(first, last, value, std::less<>{});
}
