[//]: # (Copyright 2023 Mihail Dumitrescu mhdm.dev)
[//]: # (Provided under "MIT Licence" terms.)
[//]: # (SPDX-License-Identifier: MIT)

See article at [mhdm.dev/posts/sb\_lower\_bound/](https://mhdm.dev/posts/sb_lower_bound/)

Example ways to run the benchmark:

```sh
clang++ -std=c++20 -Wall -O2 -march=haswell -mllvm -x86-cmov-converter=false test.cpp -o test && ./test
clang++ -std=c++20 -Wall -O2 -march=haswell test.cpp -o test && ./test
g++ -std=c++20 -Wall -O2 -march=haswell test.cpp -o test && ./test
```

Show the number of comparisons the `lower_bound()` variants do:

```sh
clang++ -DCOUNT_CALLS -std=c++20 -Wall -O2 test.cpp -o test && ./test
```
