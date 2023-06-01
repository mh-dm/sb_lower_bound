// Copyright 2023 Mihail Dumitrescu mhdm.dev
// Provided under "MIT Licence" terms
// SPDX-License-Identifier: MIT

#pragma once

#if !__has_builtin(__builtin_unpredictable)
   #define __builtin_unpredictable(X) __builtin_expect_with_probability(X, 0, 0.5)
#endif
