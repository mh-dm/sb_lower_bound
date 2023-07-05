// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms.
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt sbp_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = last - first;
   // Sized to roughly fit in L2 cache
   constexpr int entries_per_256KB = 256 * 1024 / sizeof(T);
   if (length >= entries_per_256KB) {
      constexpr int num_per_cache_line = std::max(64 / int(sizeof(T)), 1);
      while (length >= 3 * num_per_cache_line) {
         auto half = length / 2;
         __builtin_prefetch(&first[half / 2]);
         // length - half equals half + length % 2
         auto first_half1 = first + (length - half);
         __builtin_prefetch(&first_half1[half / 2]);
         first = comp(first[half], value) ? first_half1 : first;
         length = half;
      }
   }
   while (length > 0) {
      auto half = length / 2;
      auto first_half1 = first + (length - half);
      first = comp(first[half], value) ? first_half1 : first;
      length = half;
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt sbp_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return sbp_lower_bound(first, last, value, std::less<>{});
}
