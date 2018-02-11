//
//  tensor.hpp
//  Tests
//
//  Created by Francisco Meirinhos on 25/11/16.
//

#ifndef tensor_hpp
#define tensor_hpp

#include <cassert>
#include <type_traits>

/*
 Arbitrary Tensor Class

 Wraps a contiguous array into a tensor object.

 NOTE: No tensor contraction implemented (I wish!)
 */

template <typename T, size_t... Dim> class Tensor : public T {
  typedef typename T::value_type scalar;

public:
  /// Ctor
  Tensor(T &container) : _t(container) {
    // Assert Dimensions
    assert(strider<Dim...>::total_size == _t.size());
  }

  /// Access position
  template <typename... Coords> constexpr scalar &operator()(Coords... coords) {
    static_assert(sizeof...(Coords) == sizeof...(Dim),
                  "Tensor entries don't match tensor indexes");

    return _t.data()[tensor_at<>(strider<Dim...>(), coords...)];
  }

  template <typename... Coords>
  constexpr scalar &operator()(Coords... coords) const {
    static_assert(sizeof...(Coords) == sizeof...(Dim),
                  "Tensor entries don't match tensor indexes");

    return _t.data()[tensor_at<>(strider<Dim...>(), coords...)];
  }

  /// Assign new container
  template <typename U> T &operator=(U &newData) {
    // Check if containers have the same value type
    static_assert(std::is_same<T, U>::value, "different data structures");
    // Check if containers have the same size
    assert((*_t).size() == newData.size());
    _t = &newData;
    return *this;
  }

  T &get() { return _t; }

  const T &get() const { return _t; }

protected:
  // Container
  T &_t;

  // Tensor auxiliary struct
  template <size_t Size0, size_t... Sizes> struct strider {
    static const size_t size = Size0;
    static const size_t stride =
        strider<Sizes...>::stride * strider<Sizes...>::size;

    static const size_t total_size = size * strider<Sizes...>::total_size;
  };

  template <size_t Size0> struct strider<Size0> {
    static const size_t size = Size0;
    static const size_t stride = 1;

    static const size_t total_size = size;
  };

  // Position at (1D array) flattened tensor
  template <size_t Size0>
  static constexpr size_t tensor_at(strider<Size0>, size_t Index0) {
    return Index0;
  };

  template <size_t Size0, size_t... Sizes, typename... Indexes>
  static constexpr size_t tensor_at(strider<Size0, Sizes...>, size_t Index0,
                                    Indexes... I) {
    return Index0 + Size0 * tensor_at(strider<Sizes...>(), I...);
  };
};

#endif /* tensor_hpp */
