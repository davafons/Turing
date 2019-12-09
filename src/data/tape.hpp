#pragma once

#include <iostream>
#include <unordered_map>

#include "utils/utils.hpp"

namespace turing {

template <class T, int N> class Tape {
public:
  explicit Tape(const std::string &input_str = "");

  int size() const noexcept;

private:
  int tape_head_{0};

  std::unordered_map<int, decltype(tuple_of<N, T>())> mem_;
};

template <class T, int N> Tape<T, N>::Tape(const std::string &input_str) {}

} // namespace turing
