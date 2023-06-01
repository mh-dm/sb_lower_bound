// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under MIT Licence terms
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>
#include <iostream>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt bb_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   auto length = size_t(last - first);
   while (length & (length + 1)) {
      // 10111001 length + 2
      // 10111000 (length + 1)
      // 10110111 length
      // 10110000 length & (length + 1)
      // 10111111 length | (length + 1)
      // 01011011 length / 2
      // 01011111 (length | (length + 1)) / 2
      // auto step = length >> 1; step |= step >> 1;
      // auto step = (length | (length + 1)) / 2; step |= step >> 1;
      // auto step = length * 9 / 16; step |= step >> 1;
      // auto step = length == 2 ? 1 : (length - 3) / 6 * 4 + 3;
      // auto step = length == 2 ? 1 : (length - 4) / 5 * 4 + 3;
      // auto step = length / 2;
      // auto step = length / 4 * 2 + 1;
      // auto step = length * 5 / 16 * 2 + 1;
      // auto step = length / 3 * 2 + 1;
      // auto step = length * 3 / 4;
      // auto step = length / 4 * 3;
      // auto step = (length - 2) / 4 * 3 + 1;
      // auto step = length * 3 / 8 * 2;
      // auto step = length / 8 * 6;
      auto step = length / 8 * 6 + 1;
      // auto step = length * 3 / 8 * 2 + 1;
      // auto step = length * 4 / 5 - 1;
      // auto step = (length - 2) / 5 * 4 + 1;
      // auto step = std::bit_floor(length) - 1;			// 11825
      // auto step = std::bit_floor(length * 7 / 8) - 1;	// 11599
      // auto step = std::bit_floor(length * 4 / 5) - 1;	// 11560
      // auto step = std::bit_floor(length * 3 / 4) - 1;	// 11520
      // auto step = std::bit_floor(length * 2 / 3) - 1;	// 11507
      // auto step = std::bit_floor(length * 5 / 8) - 1;	// 11548
      if (comp(first[step], value)) {
         first += step + 1;
         length -= step + 1;
      } else {
         length = step;
         break;
      }
   }
   while (length != 0) {
      length /= 2;
      if (comp(first[length], value)) {
         first += length + 1;
      }
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt bb_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return bb_lower_bound(first, last, value, std::less<>{});
}
