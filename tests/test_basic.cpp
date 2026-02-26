#include <sort_utils/sort_utils.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace sort_utils;

static bool is_sorted_asc(const std::vector<int> &v)
{
  for (std::size_t i = 1; i < v.size(); ++i)
  {
    if (v[i - 1] > v[i])
      return false;
  }
  return true;
}

static bool is_sorted_desc_prefix(const std::vector<int> &v, std::size_t k)
{
  const std::size_t n = v.size();
  if (k > n)
    k = n;

  for (std::size_t i = 1; i < k; ++i)
  {
    if (v[i - 1] < v[i])
      return false;
  }
  return true;
}

static void test_sort_inplace()
{
  std::vector<int> v{5, 1, 4, 2, 3};
  sort_inplace(v.begin(), v.end());
  assert(is_sorted_asc(v));
}

static void test_sort_inplace_custom_comp()
{
  std::vector<int> v{1, 2, 3, 4};
  sort_inplace(v.begin(), v.end(), [](int a, int b)
               { return a > b; });
  assert(v[0] == 4 && v[1] == 3 && v[2] == 2 && v[3] == 1);
}

static void test_stable_sort_inplace_stability()
{
  // (key, original_index)
  std::vector<std::pair<int, int>> v{
      {2, 0}, {1, 1}, {2, 2}, {1, 3}, {2, 4}};

  stable_sort_inplace(v.begin(), v.end(),
                      [](const auto &a, const auto &b)
                      { return a.first < b.first; });

  // For key==1, indices should remain [1,3]
  // For key==2, indices should remain [0,2,4]
  assert(v[0].first == 1 && v[0].second == 1);
  assert(v[1].first == 1 && v[1].second == 3);
  assert(v[2].first == 2 && v[2].second == 0);
  assert(v[3].first == 2 && v[3].second == 2);
  assert(v[4].first == 2 && v[4].second == 4);
}

static void test_partial_sort_inplace()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 4;

  partial_sort_inplace(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k), v.end());

  // first k are the smallest k in sorted order: 1,2,3,4
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 3);
  assert(v[3] == 4);
}

static void test_nth_element_inplace()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 4;

  nth_element_inplace(v.begin(), v.begin() + static_cast<std::ptrdiff_t>(k), v.end());

  // Element at k is the same as if fully sorted => value 5
  assert(v[k] == 5);

  // All before k <= v[k], all after k >= v[k]
  for (std::size_t i = 0; i < k; ++i)
    assert(v[i] <= v[k]);
  for (std::size_t i = k + 1; i < v.size(); ++i)
    assert(v[i] >= v[k]);
}

static void test_top_k_smallest_inplace()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 3;

  top_k_smallest_inplace(v.begin(), v.end(), k);

  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 3);
}

static void test_top_k_largest_inplace()
{
  std::vector<int> v{9, 1, 8, 2, 7, 3, 6, 4, 5};
  const std::size_t k = 3;

  top_k_largest_inplace(v.begin(), v.end(), k);

  assert(is_sorted_desc_prefix(v, k));
  assert(v[0] == 9);
  assert(v[1] == 8);
  assert(v[2] == 7);
}

int main()
{
  test_sort_inplace();
  test_sort_inplace_custom_comp();
  test_stable_sort_inplace_stability();
  test_partial_sort_inplace();
  test_nth_element_inplace();
  test_top_k_smallest_inplace();
  test_top_k_largest_inplace();

  std::cout << "sort_utils tests passed\n";
  return 0;
}
