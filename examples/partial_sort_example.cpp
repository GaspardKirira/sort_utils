#include <sort_utils/sort_utils.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 4;

  sort_utils::partial_sort_inplace(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k), v.end());

  std::cout << "smallest " << k << " (sorted prefix): ";
  for (std::size_t i = 0; i < k; ++i)
    std::cout << v[i] << " ";
  std::cout << "\n";
}

int main()
{
  run_example();
}
