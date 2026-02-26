# sort_utils

Deterministic sorting helpers for modern C++.

`sort_utils` provides explicit, minimal wrappers around standard sorting
algorithms with clear semantics and predictable behavior.

Header-only. Zero external dependencies.

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/sort_utils

## Why sort_utils?

Standard `<algorithm>` provides powerful sorting primitives, but:

-   Naming is inconsistent (`sort`, `stable_sort`, `partial_sort`,
    `nth_element`)
-   top-k patterns require remembering the correct combination
-   Competitive programming often needs explicit prefix behavior
-   Code clarity suffers when intent is implicit

This library provides:

-   `sort_inplace`
-   `stable_sort_inplace`
-   `partial_sort_inplace`
-   `nth_element_inplace`
-   `top_k_smallest_inplace`
-   `top_k_largest_inplace`

No abstraction layers.\
No hidden allocation (beyond what `std::stable_sort` may do
internally).\
No policy objects.

Just explicit sorting primitives.

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/sort_utils
vix deps
```

### Manual

``` bash
git clone https://github.com/GaspardKirira/sort_utils.git
```

Add the `include/` directory to your project.

## Dependency

Requires C++17 or newer.

No external dependencies.

## Quick Examples

### Basic Sort

``` cpp
#include <sort_utils/sort_utils.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::vector<int> v{5, 1, 4, 2, 3};

  sort_utils::sort_inplace(v.begin(), v.end());

  for (int x : v)
    std::cout << x << " ";
}
```

### Stable Sort

``` cpp
#include <sort_utils/sort_utils.hpp>
#include <vector>
#include <iostream>
#include <utility>

int main()
{
  std::vector<std::pair<int,int>> v{
    {2,0},{1,1},{2,2},{1,3}
  };

  sort_utils::stable_sort_inplace(
    v.begin(),
    v.end(),
    [](auto& a, auto& b)
    {
      return a.first < b.first;
    });

  for (auto& p : v)
    std::cout << p.first << ":" << p.second << "\n";
}
```

### Top-K Smallest

``` cpp
#include <sort_utils/sort_utils.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::vector<int> v{9,1,8,2,7,3,6,4,5};

  sort_utils::top_k_smallest_inplace(v.begin(), v.end(), 3);

  for (int i = 0; i < 3; ++i)
    std::cout << v[i] << " ";
}
```

### nth_element

``` cpp
#include <sort_utils/sort_utils.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::vector<int> v{9,1,8,2,7,3,6,4,5};

  sort_utils::nth_element_inplace(
    v.begin(),
    v.begin() + 4,
    v.end());

  std::cout << "5th smallest: "
            << v[4]
            << "\n";
}
```

## API Overview

``` cpp
sort_utils::sort_inplace(first, last);
sort_utils::sort_inplace(first, last, comp);

sort_utils::stable_sort_inplace(first, last);
sort_utils::stable_sort_inplace(first, last, comp);

sort_utils::partial_sort_inplace(first, middle, last);
sort_utils::partial_sort_inplace(first, middle, last, comp);

sort_utils::nth_element_inplace(first, nth, last);
sort_utils::nth_element_inplace(first, nth, last, comp);

sort_utils::top_k_smallest_inplace(first, last, k);
sort_utils::top_k_largest_inplace(first, last, k);
```

All algorithms:

-   Operate in-place
-   Require random-access iterators
-   Follow standard algorithm complexity guarantees
-   Have deterministic behavior

## Design Principles

-   Explicit over implicit
-   Clear naming
-   No hidden behavior
-   Minimal surface area
-   Competitive-programming friendly
-   Production-safe

This module is intentionally small.

If you need:

-   Parallel sorting
-   Custom projection support
-   Ranges-based adapters
-   External-memory sorting

Build those on top.

## Tests

Run:

``` bash
vix build
vix tests
```

Tests verify:

-   Sorting correctness
-   Stability guarantees
-   Partial ordering behavior
-   Top-k prefix correctness

## License

MIT License
Copyright (c) Gaspard Kirira

