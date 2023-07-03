// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms.
// SPDX-License-Identifier: MIT

#include "asm_lower_bound.h"
#include "bb_lower_bound.h"
#include "bit_lower_bound.h"
#include "branchless_lower_bound.h"
#include "bstd_lower_bound.h"
#include "fb_lower_bound.h"
#include "pb_lower_bound.h"
#include "rem_lower_bound.h"
#include "sb_lower_bound.h"
#include "sbm_lower_bound.h"
#include "sbu_lower_bound.h"
#include "std_lower_bound.h"

#include <chrono>
#include <iostream>
#include <random>

#if COUNT_CALLS

typedef float Type;
typedef std::vector<Type>::iterator Iter;
typedef Iter (*Func)(Iter, Iter, const Type&, bool(Type, Type));

static int num_comp_calls = 0;

static bool comp(Type a, Type b) {
   num_comp_calls++;
   return a < b;
}

int main(int argc, char* argv[]) {
   int limit = 64;
   std::vector<Type> vec;
   Func functions[] = {
         std::lower_bound,
         std_lower_bound,
         (Func)branchless_lower_bound<Iter, Type, bool(Type, Type)>, // ugh
         asm_lower_bound,
         fb_lower_bound,
         pb_lower_bound,
         sb_lower_bound,
         bb_lower_bound};
   int comparisons[std::size(functions)] = {};
   for (int size = 1; size <= limit; size++) {
      vec.push_back(size - 1);
      std::cout << "size " << size << " comparisons";
      for (unsigned funi = 0; funi < std::size(functions); funi++) {
         num_comp_calls = 0;
         for (int i = 0; i <= size; i++) {
            auto found = functions[funi](vec.begin(), vec.end(), i, &comp);
            auto idx = found - vec.begin();
            if (idx != i) {
               std::cout << " Error! " << idx << " instead of " << i << std::endl;
               return 2;
            }
         }
         std::cout << " " << num_comp_calls;
         comparisons[funi] += num_comp_calls;
      }
      std::cout << std::endl;
   }
   std::cout << "total comparisons";
   for (unsigned funi = 0; funi < std::size(functions); funi++) {
      std::cout << " " << comparisons[funi];
   }
   std::cout << std::endl;
   return 0;
}

#else

// Change this to test searching different types of lists
// Ex: int, long, float, double, std::string
typedef float Type;
typedef std::vector<Type>::iterator Iter;
typedef Iter (*Func)(Iter, Iter, const Type&);

template <typename T> T make_vt(int value) {
   return T(value);
}

template <> __attribute__((noinline)) std::string make_vt(int value) {
   constexpr int len = 10;
   std::string res(len, 'a');
   for (int i = len - 1; i >= 0; i--) {
      res[i] += value % 16;
      value >>= 4;
   }
   return res;
}

constexpr auto make_value = make_vt<Type>;

int main() {
   using std::chrono::high_resolution_clock;
   Func functions[] = {
         // Ignore results from first run function as it has a measurable disadvantage.
         std_lower_bound,
         std::lower_bound,
         branchless_lower_bound,
         // asm_lower_bound,
         // bstd_lower_bound,
         // rem_lower_bound,
         // fb_lower_bound,
         // pb_lower_bound,
         sb_lower_bound,
         sbm_lower_bound,
         // sbu_lower_bound,
         bb_lower_bound};
   double times[std::size(functions)] = {};
   std::minstd_rand rand;
   long stride = 100007;
   // int stride = 1;
   int max_calls = 200000;
   // int limit = 32;
   int limit = 1024 * 1024 * (std::is_same<Type, std::string>::value ? 1 : 4);
   // std::cout << make_value(limit) << std::endl;
   int sizes = 0;
   int last = 0;
   std::vector<Type> vec;
   for (int size = 0; size <= limit; size = size * 1.1 + 1) {
      sizes++;
      for (; last < size; last++) {
         vec.push_back(make_value(last));
      }
      int checks = size + 1;
      int calls = checks * (max_calls / checks + 1);
      std::vector<int> shuffled(calls);
      for (int i = 0; i < calls; i++) {
         shuffled[i] = (stride * i) % checks;
      }
      rand.seed(1);
      std::shuffle(shuffled.begin(), shuffled.end(), rand);
      calls = max_calls;

      std::cout << "size\t" << vec.size() << "\t";
      for (unsigned funi = 0; funi < std::size(functions); funi++) {
         auto t0 = high_resolution_clock::now();
         for (int i = 0; i < calls; i++) {
            Type value = make_value(shuffled[i]);
            auto res = functions[funi](vec.begin(), vec.end(), value);
            auto found = res - vec.begin();
            if (found != shuffled[i]) {
               std::cout << " Error! " << found << " instead of " << shuffled[i] << std::endl;
               return 2;
            }
         }
         auto time = high_resolution_clock::now() - t0;
         std::cout << time.count() / calls << "\t";
         times[funi] += double(time.count()) / calls;
      }
      std::cout << std::endl;
   }
   for (auto& time : times) {
      std::cout << time / sizes << " ";
   }
   std::cout << std::endl;
}
#endif
