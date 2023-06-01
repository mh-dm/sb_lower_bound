// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms
// SPDX-License-Identifier: MIT

#pragma once

#include <bit>
#include <functional>

template <class ForwardIt, class T, class Compare>
constexpr ForwardIt asm_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
   // Works for x86 only
   auto length = last - first;
   while (length > 0) {
      auto rem = length % 2;
      length /= 2;
      auto firstplus = first + length + rem;
      // Does a comparison which sets some x86 FLAGS like CF or ZF
      bool compare = comp(first[length], value);
      // Inline assembly doesn't support passing bools straight into FLAGS
      // so we ask the compiler to copy it from FLAGS into a register
      __asm__(
            // Then we test the register, which sets ZF=!compare and CF=0
            // Reference: https://www.felixcloutier.com/x86/test
            "test %[compare],%[compare]\n"
            // cmova copies firstplus into first if ZF=0 and CF=0
            // Reference: https://www.felixcloutier.com/x86/cmovv
            "cmova %[firstplus],%[first]\n"
            : [first] "+r"(first)
            : [firstplus] "r"(firstplus), [compare] "r"(compare));
   }
   return first;
}

template <class ForwardIt, class T>
constexpr ForwardIt asm_lower_bound(ForwardIt first, ForwardIt last, const T& value) {
   return asm_lower_bound(first, last, value, std::less<>{});
}
