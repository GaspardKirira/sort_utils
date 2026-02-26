#include <sort_utils/sort_utils.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 4;

  sort_utils::nth_element_inplace(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k), v.end());

  std::cout << "element at index " << k << " after nth_element: " << v[k] << "\n";
  std::cout << "note: prefix/suffix are partitioned, not fully sorted\n";
}

int main()
{
  run_example();
}
