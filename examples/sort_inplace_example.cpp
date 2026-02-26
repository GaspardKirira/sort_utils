#include <sort_utils/sort_utils.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  std::vector<int> v{5, 1, 4, 2, 3};

  sort_utils::sort_inplace(v.begin(), v.end());

  std::cout << "sorted: ";
  for (int x : v)
    std::cout << x << " ";
  std::cout << "\n";
}

int main()
{
  run_example();
}
