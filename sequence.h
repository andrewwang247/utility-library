/*
Copyright 2026. Andrew Wang.

Operations over sequences.
*/
#pragma once

#include <iterator>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

/**
 * Split container into a list of containers delimited
 * by the given delimiter parameter.
 */
template <typename Container, typename T>
std::vector<Container> split(const Container &items, const T &delim) {
  std::vector<Container> tokens;
  for (auto iter = items.begin(); iter != items.end();) {
    auto spot = find(iter, items.end(), delim);
    if (iter != spot) tokens.emplace_back(iter, spot);
    iter = (spot == items.end()) ? items.end() : std::next(spot);
  }
  return tokens;
}

template <>
std::vector<std::string> split<std::string, std::string>(
    const std::string &items, const std::string &delim) {
  if (delim.empty()) throw std::out_of_range("Delimiter cannot be empty.");
  if (delim.size() == 1) return split<std::string, char>(items, delim.front());
  std::vector<size_t> positions;
  for (auto pos = items.find(delim, 0); pos != std::string::npos;
       pos = items.find(delim, pos + 1)) {
    positions.emplace_back(pos);
  }
  std::vector<std::string> tokens;
  // Upper bound on number of tokens.
  tokens.reserve(positions.size() + 1);
  // Skip ranges { [ pos, pos + delim.size() ) : pos in positions }
  for (size_t base = 0, index = 0; index < positions.size(); ++index) {
    auto pos = positions[index];
    if (base != pos) tokens.emplace_back(items.substr(base, pos - base));
    base = pos + delim.size();
  }
  return tokens;
}

/**
 * Join a range of items with a separator.
 */
template <typename Iter, typename T>
auto join(Iter begin, Iter end, T sep) {
  auto value = *begin;
  for (auto iter = std::next(begin); iter != end; ++iter) {
    value += sep;
    value += *iter;
  }
  return value;
}

/**
 * Python style container slicing that follows usual Python semantics.
 * REQUIRES: Container has bi-directional iteration and range construction.
 * THROWS: std::out_of_range for start, stop, and step parameters.
 */
template <typename Container>
Container slice(const Container &items,
                std::optional<ptrdiff_t> start = std::nullopt,
                std::optional<ptrdiff_t> stop = std::nullopt,
                std::optional<ptrdiff_t> step = std::nullopt) {
  // Default step value is 1.
  const auto resolved_step = step.value_or(1);
  if (resolved_step == 0) throw std::out_of_range("Step must be non-zero.");

  // Default start value depends on sign of step.
  const auto resolved_start =
      resolved_step > 0 ? start.value_or(0) : start.value_or(items.size() - 1);
  // Valid if step is positive. Else should be one before begin.
  const auto resolved_stop =
      stop.value_or(static_cast<ptrdiff_t>(items.size()));

  // Check that start and stop are within bounds.
  auto absolute = [](auto num) { return num >= 0 ? num : -num; };
  if (static_cast<size_t>(absolute(resolved_start)) > items.size()) {
    throw std::out_of_range("Start parameter out of range.");
  }
  if (static_cast<size_t>(absolute(resolved_stop)) > items.size()) {
    throw std::out_of_range("Stop parameter out of range.");
  }

  // Convert indices to iterators.
  auto signed_iter = [&items](auto index) {
    return index >= 0 ? std::next(items.begin(), index)
                      : std::prev(items.end(), -index);
  };
  const auto b_iter = signed_iter(resolved_start);
  const auto e_iter = signed_iter(resolved_stop);

  // Check if iter is still within bounds.
  auto bound_check = [&items, &stop, resolved_step, &e_iter](const auto &iter) {
    // If this is the case, the e_iter is valid.
    if (resolved_step > 0) {
      return iter < e_iter;
    }
    // Otherwise, we need to see if stop was given.
    if (stop.has_value()) {
      return (resolved_step > 0) ? (iter < e_iter) : (iter > e_iter);
    } else {
      return iter >= items.begin();
    }
  };

  std::vector<typename Container::value_type> history;
  for (auto it = b_iter; bound_check(it); std::advance(it, resolved_step)) {
    history.emplace_back(*it);
  }
  return Container(history.begin(), history.end());
}
