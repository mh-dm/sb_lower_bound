// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

using std::bit_floor;

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt fb_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = size_t(last - first);
   if (length & (length + 1)) {
      // auto step = length - bit_floor(length);
      // auto step = length - bit_floor(length * 4 / 5);
      // auto step = length - bit_floor(length * 3 / 4);
      auto step = length - bit_floor(length * 2 / 3); // Most optimal.
      // auto step = length - bit_floor(length * 3 / 5);
      // auto step = length - bit_floor(length / 2);
      if (comp(first[step], value)) {
         first += step + 1;
         length = last - first;
      } else {
         length = step;
      }
   }
   while (length > 0) {
      length /= 2;
      if (comp(first[length], value)) {
         first += length + 1;
      }
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt fb_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return fb_lower_bound(first, last, value, std::less<>{});
}
