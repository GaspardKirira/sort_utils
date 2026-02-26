#include <sort_utils/sort_utils.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 3;

  sort_utils::top_k_smallest_inplace(v.begin(), v.end(), k);

  std::cout << "top " << k << " smallest: ";
  for (std::size_t i = 0; i < k; ++i)
    std::cout << v[i] << " ";
  std::cout << "\n";
}

int main()
{
  run_example();
}
