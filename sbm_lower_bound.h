// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms.
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt sbm_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = last - first;
   while (length > 0) {
      auto rem = length % 2;
      length /= 2;
      // gcc generates a cmov with a multiply instead of a ternary conditional
      first += comp(first[length], value) * (length + rem);
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt sbm_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return sbm_lower_bound(first, last, value, std::less<>{});
}
