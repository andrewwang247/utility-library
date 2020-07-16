/*
Copyright 2020. Siwei Wang.

Python-like cartesian product iteration for two containers.
*/

#pragma once

#include <iterator>
#include <utility>

/**
 * Templated product class for read-only cartesian product iteration.
 * REQUIRES: C1 and C2 are forward_iterable.
 */
template <typename C1, typename C2>
class product {
 private:
  const C1 &container_1;
  const C2 &container_2;

 public:
  product() = delete;

  /**
   * Product should be passed the two containers to iterate over.
   */
  product(const C1 &, const C2 &);

  class iterator
      : public std::iterator<
            std::forward_iterator_tag,
            std::pair<typename C1::value_type, typename C2::value_type>,
            ptrdiff_t,
            const std::pair<typename C1::value_type, typename C2::value_type> *,
            const std::pair<typename C1::value_type, typename C2::value_type>
                &> {
    friend class product;

   private:
    typename C2::const_iterator c2_begin;
    typename C2::const_iterator c2_end;

    typename C1::const_iterator c1_current;
    typename C2::const_iterator c2_current;

    /**
     * Constructor that gives parameters.
     */
    explicit iterator(typename C2::const_iterator, typename C2::const_iterator,
                      typename C1::const_iterator, typename C2::const_iterator);

   public:
    iterator() = delete;

    // Increment operator.

    iterator &operator++();
    iterator operator++(int);

    // Dereference operator.

    std::pair<typename C1::value_type, typename C2::value_type> operator*()
        const;

    // These iterators do not support arrow operators.

    // Comparison operators.

    bool operator==(const iterator &) const;
    bool operator!=(const iterator &) const;
  };

  /**
   * An iterator to the first pair.
   */
  iterator begin() const;

  /**
   * An iterator to one past the last pair.
   */
  iterator end() const;
};

/* --- TEMPLATE IMPLEMENTATION --- */

template <typename C1, typename C2>
inline product<C1, C2>::product(const C1 &c1, const C2 &c2)
    : container_1(c1), container_2(c2) {}

template <typename C1, typename C2>
inline typename product<C1, C2>::iterator product<C1, C2>::begin() const {
  return iterator(container_2.cbegin(), container_2.cend(),
                  container_1.cbegin(), container_2.cbegin());
}

template <typename C1, typename C2>
inline typename product<C1, C2>::iterator product<C1, C2>::end() const {
  return iterator(container_2.cbegin(), container_2.cend(), container_1.cend(),
                  container_2.cbegin());
}

template <typename C1, typename C2>
inline product<C1, C2>::iterator::iterator(typename C2::const_iterator c2_b,
                                           typename C2::const_iterator c2_e,
                                           typename C1::const_iterator c1_c,
                                           typename C2::const_iterator c2_c)
    : c2_begin(c2_b), c2_end(c2_e), c1_current(c1_c), c2_current(c2_c) {}

template <typename C1, typename C2>
inline typename product<C1, C2>::iterator &product<C1, C2>::iterator::
operator++() {
  if (++c2_current == c2_end) {
    c2_current = c2_begin;
    ++c1_current;
  }
  return *this;
}

template <typename C1, typename C2>
inline typename product<C1, C2>::iterator product<C1, C2>::iterator::operator++(
    int) {
  auto temp(*this);
  this->operator++();
  return temp;
}

template <typename C1, typename C2>
inline std::pair<typename C1::value_type, typename C2::value_type>
    product<C1, C2>::iterator::operator*() const {
  return std::make_pair(*c1_current, *c2_current);
}

template <typename C1, typename C2>
inline bool product<C1, C2>::iterator::operator==(
    const typename product<C1, C2>::iterator &other) const {
  return c1_current == other.c1_current && c2_current == other.c2_current;
}

template <typename C1, typename C2>
inline bool product<C1, C2>::iterator::operator!=(
    const typename product<C1, C2>::iterator &other) const {
  return c1_current != other.c1_current || c2_current != other.c2_current;
}
