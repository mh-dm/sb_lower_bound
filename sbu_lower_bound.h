// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms.
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

#define FOR_EACH_2(F, X) F(X) F(X - 1)
#define FOR_EACH_4(F, X) FOR_EACH_2(F, X) FOR_EACH_2(F, X - 2)
#define FOR_EACH_8(F, X) FOR_EACH_4(F, X) FOR_EACH_4(F, X - 4)
#define FOR_EACH_16(F, X) FOR_EACH_8(F, X) FOR_EACH_8(F, X - 8)
#define FOR_EACH_32(F, X) FOR_EACH_16(F, X) FOR_EACH_16(F, X - 16)
#define FOR_EACH_64(F, X) FOR_EACH_32(F, X) FOR_EACH_32(F, X - 32)

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt sbu_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   size_t length = last - first;
   size_t rem;
   switch (std::bit_width(length)) {
#define GEN_CASE(X) \
   case X: \
      rem = length % 2; \
      length /= 2; \
      first += comp(first[length], value) * (length + rem);

      FOR_EACH_64(GEN_CASE, 64);
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt sbu_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return sbu_lower_bound(first, last, value, std::less<>{});
}
