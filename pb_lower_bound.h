// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt pb_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = size_t(last - first);
   auto step = std::bit_floor(length + 1) - 1;
   while (step != length && comp(first[step], value)) {
      first += step + 1;
      length = last - first;
      step = std::bit_floor(length + 1) - 1;
   }
   while (step != 0) {
      step /= 2;
      if (comp(first[step], value)) {
         first += step + 1;
      }
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt pb_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return pb_lower_bound(first, last, value, std::less<>{});
}
