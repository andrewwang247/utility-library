/*
Copyright 2020. Siwei Wang.

Python-like parallel iteration for two containers.
*/
#pragma once

#include <iterator>
#include <utility>

/**
 * Templated zipper class for read-only parallel iteration.
 * REQUIRES: c1 and c2 are forward_iterable.
 */
template <typename C1, typename C2>
class zip {
 private:
  const C1 &container_1;
  const C2 &container_2;

 public:
  zip() = delete;

  /**
   * Zip should be passed the two containers to iterate over.
   */
  zip(const C1 &, const C2 &);

  // Declare forward iterators.
  class iterator
      : public std::iterator<
            std::forward_iterator_tag,
            std::pair<typename C1::value_type, typename C2::value_type>,
            ptrdiff_t,
            const std::pair<typename C1::value_type, typename C2::value_type> *,
            const std::pair<typename C1::value_type, typename C2::value_type>
                &> {
    friend class zip;

   private:
    typename C1::const_iterator c1_it;
    typename C2::const_iterator c2_it;

    /**
     * Constructor that gives parameters.
     */
    explicit iterator(typename C1::const_iterator, typename C2::const_iterator);

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
   * An iterator to the first element.
   */
  iterator begin() const;

  /**
   * An iterator to one past the last element.
   */
  iterator end() const;
};

/* --- TEMPLATE IMPLEMENTATION --- */

template <typename C1, typename C2>
inline zip<C1, C2>::zip(const C1 &c1, const C2 &c2)
    : container_1(c1), container_2(c2) {}

template <typename C1, typename C2>
inline typename zip<C1, C2>::iterator zip<C1, C2>::begin() const {
  return iterator(container_1.cbegin(), container_2.cbegin());
}

template <typename C1, typename C2>
inline typename zip<C1, C2>::iterator zip<C1, C2>::end() const {
  const auto sz_1 = container_1.size();
  const auto sz_2 = container_2.size();
  if (sz_1 < sz_2) {
    const auto iter = std::next(container_2.cbegin(), sz_1);
    return iterator(container_1.cend(), iter);
  } else {
    const auto iter = std::next(container_1.cbegin(), sz_2);
    return iterator(iter, container_2.cend());
  }
}

template <typename C1, typename C2>
inline zip<C1, C2>::iterator::iterator(typename C1::const_iterator it1,
                                       typename C2::const_iterator it2)
    : c1_it(it1), c2_it(it2) {}

template <typename C1, typename C2>
inline typename zip<C1, C2>::iterator &zip<C1, C2>::iterator::operator++() {
  ++c1_it;
  ++c2_it;
  return *this;
}

template <typename C1, typename C2>
inline typename zip<C1, C2>::iterator zip<C1, C2>::iterator::operator++(int) {
  auto temp(*this);
  ++c1_it;
  ++c2_it;
  return temp;
}

template <typename C1, typename C2>
inline std::pair<typename C1::value_type, typename C2::value_type>
    zip<C1, C2>::iterator::operator*() const {
  return std::make_pair(*c1_it, *c2_it);
}

template <typename C1, typename C2>
inline bool zip<C1, C2>::iterator::operator==(
    const typename zip<C1, C2>::iterator &other) const {
  return c1_it == other.c1_it && c2_it == other.c2_it;
}

template <typename C1, typename C2>
inline bool zip<C1, C2>::iterator::operator!=(
    const typename zip<C1, C2>::iterator &other) const {
  return c1_it != other.c1_it || c2_it != other.c2_it;
}
