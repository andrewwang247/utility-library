/*
Copyright 2020. Siwei Wang.

Iteration over a range of consecutive numbers.
*/
#pragma once

#include <functional>
#include <iterator>

template <typename T>
class range {
 private:
  const T m_start;
  const T m_stop;

 public:
  range() = delete;

  /**
   * Represents range [0, stop), possibly reversed.
   */
  explicit range(T stop);

  /**
   * Represents range [start, stop), possibly reversed.
   */
  explicit range(T start, T stop);

  /**
   * Bidirectional iterators on range.
   */
  class iterator : public std::iterator<std::bidirectional_iterator_tag, T,
                                        ptrdiff_t, const T *, const T &> {
    friend class range;

   private:
    /**
     * Current location of this iterator.
     */
    T m_current;

    /**
     * Stops when compares current false.
     */
    const T m_limit;

    /**
     * Determines whether the direction of iteration
     * is forward (++) or backward (--).
     */
    const bool is_forward;

    /**
     * All argument constructor used by range.
     */
    iterator(T current, T limit, bool direction);

   public:
    iterator() = delete;

    // Increment operator.

    iterator &operator++();
    iterator operator++(int);

    // Decrement operator.

    iterator &operator--();
    iterator operator--(int);

    // Dereference operator.

    T operator*() const;

    // These iterators do not support arrow operators.

    // Comparison operators.

    bool operator==(const iterator &) const;
    bool operator!=(const iterator &) const;
  };

  /**
   * An iterator to the first item in the range.
   */
  iterator begin() const;

  /**
   * An iterator to one past the last item in the range.
   */
  iterator end() const;
};

template <typename T>
inline range<T>::range(T stop) : range(0, stop) {}

template <typename T>
inline range<T>::range(T start, T stop) : m_start(start), m_stop(stop) {}

template <typename T>
inline typename range<T>::iterator range<T>::begin() const {
  return iterator(m_start, m_stop, m_start < m_stop);
}

template <typename T>
inline typename range<T>::iterator range<T>::end() const {
  return iterator(m_stop, m_stop, m_start < m_stop);
}

template <typename T>
inline range<T>::iterator::iterator(T current, T limit, bool direction)
    : m_current(current), m_limit(limit), is_forward(direction) {}

template <typename T>
inline typename range<T>::iterator &range<T>::iterator::operator++() {
  is_forward ? ++m_current : --m_current;
  return *this;
}

template <typename T>
inline typename range<T>::iterator range<T>::iterator::operator++(int) {
  auto temp(*this);
  this->operator++();
  return temp;
}

template <typename T>
inline typename range<T>::iterator &range<T>::iterator::operator--() {
  is_forward ? --m_current : ++m_current;
  return *this;
}

template <typename T>
inline typename range<T>::iterator range<T>::iterator::operator--(int) {
  auto temp(*this);
  this->operator--();
  return temp;
}

template <typename T>
inline T range<T>::iterator::operator*() const {
  return m_current;
}

template <typename T>
inline bool range<T>::iterator::operator==(
    const typename range<T>::iterator &other) const {
  return m_current == other.m_current;
}

template <typename T>
inline bool range<T>::iterator::operator!=(
    const typename range<T>::iterator &other) const {
  return m_current != other.m_current;
}
