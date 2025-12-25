/*
Copyright 2020. Siwei Wang.

Python-like enumerate for iteration with index.
*/
#pragma once

#include <iterator>
#include <utility>

/**
 * Templated enumerator class for read-only enumerated iteration.
 * REQUIRES: C is forward iterable.
 */
template <typename C>
class enumerate {
 private:
  const C &container;
  const size_t start;

 public:
  enumerate() = delete;

  /**
   * Enumerate object constructed with default index starting at 0.
   */
  explicit enumerate(const C &, size_t = 0);

  // Declare forward iterators.
  class iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<size_t, typename C::value_type>;
    using difference_type = ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;
    friend class enumerate;

   private:
    typename C::const_iterator iter;
    size_t sz;

    /**
     * Constructor that gives parameters.
     */
    explicit iterator(size_t, typename C::const_iterator);

   public:
    iterator() = delete;

    // Increment operator.

    iterator &operator++();
    iterator operator++(int);

    // Dereference operator.

    std::pair<size_t, typename C::value_type> operator*() const;

    // These iterators do not support arrow operators.

    // Comparison operators.

    bool operator==(const iterator &) const;
    bool operator!=(const iterator &) const;
  };

  /**
   * An enumerated iterator to the first element.
   */
  iterator begin() const;

  /**
   * An enumerated iterator to one past the last element.
   */
  iterator end() const;
};

/* --- TEMPLATE IMPLEMENTATION --- */

template <typename C>
inline enumerate<C>::enumerate(const C &items, size_t start_in)
    : container(items), start(start_in) {}

template <typename C>
inline typename enumerate<C>::iterator enumerate<C>::begin() const {
  return iterator(start, container.cbegin());
}

template <typename C>
inline typename enumerate<C>::iterator enumerate<C>::end() const {
  return iterator(start + container.size(), container.cend());
}

template <typename C>
inline enumerate<C>::iterator::iterator(size_t sz_in,
                                        typename C::const_iterator iter_in)
    : iter(iter_in), sz(sz_in) {}

template <typename C>
inline typename enumerate<C>::iterator &enumerate<C>::iterator::operator++() {
  ++iter;
  ++sz;
  return *this;
}

template <typename C>
inline typename enumerate<C>::iterator enumerate<C>::iterator::operator++(int) {
  auto temp(*this);
  ++iter;
  ++sz;
  return temp;
}

template <typename C>
inline std::pair<size_t, typename C::value_type> enumerate<C>::iterator::
operator*() const {
  return std::make_pair(sz, *iter);
}

template <typename C>
inline bool enumerate<C>::iterator::operator==(
    const typename enumerate<C>::iterator &other) const {
  return iter == other.iter && sz == other.sz;
}

template <typename C>
inline bool enumerate<C>::iterator::operator!=(
    const typename enumerate<C>::iterator &other) const {
  return iter != other.iter || sz != other.sz;
}
