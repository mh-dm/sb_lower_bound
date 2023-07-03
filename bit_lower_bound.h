#pragma once

#include <bit>
#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt bit_lower_bound(ForwardIt begin, ForwardIt end, const T& value, Compare comp) {
   // Source: https://orlp.net/blog/bitwise-binary-search/
   // zlib license as per https://orlp.net/
   size_t n = end - begin;
   if (n == 0)
      return begin;

   size_t two_k = size_t(1) << (std::bit_width(n) - 1);
   size_t b = comp(begin[n / 2], value) ? n - two_k : -1;
   for (size_t bit = two_k >> 1; bit != 0; bit >>= 1) {
      if (comp(begin[b + bit], value))
         b += bit;
   }
   return begin + (b + 1);
}

template <class ForwardIt, class T>
constexpr ForwardIt bit_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return bit_lower_bound(first, last, value, std::less<>{});
}
