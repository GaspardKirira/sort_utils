/**
 * @file sort_utils.hpp
 * @brief Deterministic sorting helpers for modern C++.
 *
 * Provides:
 *  - sort_inplace / stable_sort_inplace wrappers
 *  - partial_sort_inplace
 *  - nth_element_inplace
 *  - top_k_smallest_inplace / top_k_largest_inplace (prefix results)
 *
 * All functions are explicit wrappers around standard algorithms with
 * consistent naming, clear preconditions, and deterministic behavior.
 *
 * No allocations.
 * No exceptions (beyond what user comparators may throw).
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace sort_utils
{

  /**
   * @brief Sorts a range in-place using std::sort.
   *
   * @tparam RandomIt Random access iterator
   *
   * @param first Begin iterator
   * @param last End iterator
   *
   * @complexity O(n log n)
   */
  template <typename RandomIt>
  void sort_inplace(RandomIt first, RandomIt last)
  {
    std::sort(first, last);
  }

  /**
   * @brief Sorts a range in-place using std::sort with a comparator.
   *
   * @tparam RandomIt Random access iterator
   * @tparam Compare Strict weak ordering comparator
   */
  template <typename RandomIt, typename Compare>
  void sort_inplace(RandomIt first, RandomIt last, Compare comp)
  {
    std::sort(first, last, comp);
  }

  /**
   * @brief Stable sorts a range in-place using std::stable_sort.
   *
   * @tparam RandomIt Random access iterator
   *
   * @complexity O(n log n) comparisons, may allocate internally (implementation-defined).
   */
  template <typename RandomIt>
  void stable_sort_inplace(RandomIt first, RandomIt last)
  {
    std::stable_sort(first, last);
  }

  /**
   * @brief Stable sorts a range in-place using std::stable_sort with a comparator.
   *
   * @tparam RandomIt Random access iterator
   * @tparam Compare Strict weak ordering comparator
   */
  template <typename RandomIt, typename Compare>
  void stable_sort_inplace(RandomIt first, RandomIt last, Compare comp)
  {
    std::stable_sort(first, last, comp);
  }

  /**
   * @brief Partially sorts so that [first, middle) contains the smallest elements in sorted order.
   *
   * Equivalent to std::partial_sort(first, middle, last).
   *
   * @tparam RandomIt Random access iterator
   *
   * @param first Begin iterator
   * @param middle Middle iterator (end of sorted prefix)
   * @param last End iterator
   *
   * @complexity O(n log k) where k = distance(first, middle)
   */
  template <typename RandomIt>
  void partial_sort_inplace(RandomIt first, RandomIt middle, RandomIt last)
  {
    std::partial_sort(first, middle, last);
  }

  /**
   * @brief Partially sorts with comparator so that [first, middle) contains the smallest elements in sorted order.
   *
   * @tparam RandomIt Random access iterator
   * @tparam Compare Strict weak ordering comparator
   */
  template <typename RandomIt, typename Compare>
  void partial_sort_inplace(RandomIt first, RandomIt middle, RandomIt last, Compare comp)
  {
    std::partial_sort(first, middle, last, comp);
  }

  /**
   * @brief Reorders range so that element at nth is the one that would be there in sorted order.
   *
   * Elements before nth are <= *nth, elements after nth are >= *nth (according to comparator).
   *
   * @tparam RandomIt Random access iterator
   *
   * @complexity O(n) average
   */
  template <typename RandomIt>
  void nth_element_inplace(RandomIt first, RandomIt nth, RandomIt last)
  {
    std::nth_element(first, nth, last);
  }

  /**
   * @brief nth_element with comparator.
   *
   * @tparam RandomIt Random access iterator
   * @tparam Compare Strict weak ordering comparator
   */
  template <typename RandomIt, typename Compare>
  void nth_element_inplace(RandomIt first, RandomIt nth, RandomIt last, Compare comp)
  {
    std::nth_element(first, nth, last, comp);
  }

  /**
   * @brief Produces the k smallest elements as a sorted prefix in-place.
   *
   * After this call:
   *  - [first, first+k) is sorted
   *  - It contains the k smallest values from the original range
   *  - The rest of the range is unspecified
   *
   * If k >= n, this becomes a full sort.
   *
   * @tparam RandomIt Random access iterator
   *
   * @param first Begin iterator
   * @param last End iterator
   * @param k Number of smallest elements to keep as sorted prefix
   *
   * @complexity O(n log k)
   */
  template <typename RandomIt>
  void top_k_smallest_inplace(RandomIt first, RandomIt last, std::size_t k)
  {
    const std::size_t n = static_cast<std::size_t>(std::distance(first, last));
    if (k == 0 || n == 0)
      return;

    if (k >= n)
    {
      std::sort(first, last);
      return;
    }

    RandomIt mid = first + static_cast<std::ptrdiff_t>(k);
    std::partial_sort(first, mid, last);
  }

  /**
   * @brief Produces the k largest elements as a sorted prefix in-place.
   *
   * After this call:
   *  - [first, first+k) is sorted in descending order
   *  - It contains the k largest values from the original range
   *  - The rest of the range is unspecified
   *
   * If k >= n, this becomes a full sort (descending).
   *
   * @tparam RandomIt Random access iterator
   *
   * @complexity O(n log k)
   */
  template <typename RandomIt>
  void top_k_largest_inplace(RandomIt first, RandomIt last, std::size_t k)
  {
    const std::size_t n = static_cast<std::size_t>(std::distance(first, last));
    if (k == 0 || n == 0)
      return;

    if (k >= n)
    {
      std::sort(first, last, std::greater<typename std::iterator_traits<RandomIt>::value_type>{});
      return;
    }

    RandomIt mid = first + static_cast<std::ptrdiff_t>(k);
    std::partial_sort(first, mid, last,
                      std::greater<typename std::iterator_traits<RandomIt>::value_type>{});
  }

} // namespace sort_utils
