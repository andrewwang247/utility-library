/*
Copyright 2020. Siwei Wang.

Tools for input output.
*/
#pragma once

#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * Parse command line arguments into a vector
 * of a given type. Attempts to perform conversion.
 */
template <typename T = std::string>
std::vector<T> argparse(int argc, char **argv) {
  // Get some qualifications out of the way.
  static_assert(!std::is_const_v<T>);
  static_assert(!std::is_pointer_v<T> && !std::is_reference_v<T>);
  static_assert(!std::is_same_v<T, char>);
  static_assert(std::is_same_v<T, std::string> || std::is_arithmetic_v<T>);
  // Prepare and reserve a vector to store items.
  std::vector<T> items;
  items.reserve(argc - 1);
  // The type is either a string or a numerical type.
  for (int i = 1; i < argc; ++i) {
    if constexpr (std::is_same_v<T, std::string>) {
      items.emplace_back(argv[i]);
    } else if constexpr (std::is_floating_point_v<T>) {
      items.emplace_back(static_cast<T>(std::strtold(argv[i], nullptr)));
    } else if constexpr (std::is_signed_v<T>) {
      items.emplace_back(static_cast<T>(std::strtoll(argv[i], nullptr, 10)));
    } else {
      items.emplace_back(static_cast<T>(std::strtoull(argv[i], nullptr, 10)));
    }
  }
  return items;
}

/**
 * Basic printing utility for pairs of any type.
 */
template <typename S, typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<S, T> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}

/**
 * Prints all items in the range [begin, end) to cout.
 * Entries are separated by sep.
 */
template <typename InputIterator>
void print_range(InputIterator start, InputIterator stop,
                 std::string sep = " ", std::string end = "\n",
                 std::ostream &os = std::cout) {
  for (auto iter = start; iter != stop; ++iter) {
    if (std::next(iter) != stop)
      os << *iter << sep;
    else
      os << *iter << end;
  }
}

/**
 * Returns the character or word count in the file.
 */
template <typename T>
size_t wc(const std::string &filename) {
  std::ifstream fin(filename);
  if constexpr (sizeof(T) == 1) fin >> std::noskipws;
  size_t counter = 0;
  for (T c; fin >> c; ++counter) continue;
  return counter;
}

// Used for template specialization of wc.
struct line {};

template <>
size_t wc<line>(const std::string &filename) {
  std::ifstream fin(filename);
  size_t counter = 0;
  for (std::string line; std::getline(fin, line); ++counter) continue;
  return counter;
}
