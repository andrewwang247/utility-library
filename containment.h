/*
Copyright 2026. Andrew Wang.

Containment checking for STL containers.
*/
#pragma once

#include <algorithm>
#include <iterator>
#include <set>
#include <type_traits>
#include <unordered_set>

/**
 * REQUIRES: Container has non-associative STL container semantics.
 * Returns whether or not the value is contained within.
 */
template <typename Container>
inline bool contains(const Container &items,
                     const typename Container::value_type &target) {
  using T = typename Container::value_type;
  if constexpr (std::is_same_v<Container, std::unordered_set<T>> ||
                std::is_same_v<Container, std::set<T>>) {
    return items.find(target) != items.end();
  } else {
    return std::find(items.begin(), items.end(), target) != items.end();
  }
}

/**
 * Specialized container checking for C-style arrays.
 */
template <size_t N, typename T>
inline bool contains(const T *const items, const T &target) {
  return std::find(items, items + N, target) != std::next(items, N);
}

/**
 * REQUIRES: Container has associative STL container semantics.
 * Returns whether or not the key is container within.
 */
template <typename Container>
inline bool contains_key(const Container &items,
                         const typename Container::key_type &target) {
  return items.find(target) != items.end();
}
