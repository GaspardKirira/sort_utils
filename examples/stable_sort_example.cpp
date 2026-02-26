#include <sort_utils/sort_utils.hpp>
#include <iostream>
#include <utility>
#include <vector>

using Pair = std::pair<int, int>; // (key, original_index)

void run_example()
{
  std::vector<Pair> v{{2, 0}, {1, 1}, {2, 2}, {1, 3}, {2, 4}};

  sort_utils::stable_sort_inplace(
      v.begin(),
      v.end(),
      [](const Pair &a, const Pair &b)
      { return a.first < b.first; });

  std::cout << "stable sorted by key:\n";
  for (const auto &p : v)
    std::cout << "  (" << p.first << ", " << p.second << ")\n";
}

int main()
{
  run_example();
}
