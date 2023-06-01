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
      auto rem = length % 2;
      length /= 2;
      if (comp(first[length], value)) {
         first += length + rem;
      }
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt sb_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return sb_lower_bound(first, last, value, std::less<>{});
}
