#pragma once

#include <iostream>
#include <sstream>
#include <unordered_map>

#include "data/alphabet.hpp"
#include "utils/utils.hpp"

namespace turing {

template <int nTracks> class Tape {
public:
  using Column = std::array<Symbol, nTracks>;

public:
  explicit Tape(const std::string &input_str = "",
                const std::string &alphabet_str = "");

  Alphabet &alphabet();
  const Alphabet &alphabet() const;

  int size() const noexcept;
  int numTracks() const noexcept;

  template <int N = nTracks, typename std::enable_if_t<(N == 1), int> = 0>
  Symbol &peek();

  template <int N = nTracks, typename std::enable_if_t<(N == 1), int> = 0>
  const Symbol &peek() const;

  template <int N = nTracks, typename std::enable_if_t<(N > 1), int> = 0>
  Column &peek();

  template <int N = nTracks, typename std::enable_if_t<(N > 1), int> = 0>
  const Column &peek() const;

  void moveLeft();
  void moveRight();

  void reset();

  void setInputString(const std::string &input_str);

  //
  // template <int N>
  // friend std::ostream &operator<<(std::ostream &os, const Tape<N> &tape);

private:
  Column &at(int idx);
  const Column &at(int idx) const;

private:
  int tape_head_{0};

  mutable std::unordered_map<int, Column> mem_;

  Alphabet alphabet_;
};

template <int nTracks>
Tape<nTracks>::Tape(const std::string &input_str,
                    const std::string &alphabet_str) {
  if (alphabet_str.empty()) {
    alphabet_.addSymbols(input_str);
  } else {
    alphabet_.addSymbols(alphabet_str);
  }

  setInputString(input_str);
}

template <int nTracks> Alphabet &Tape<nTracks>::alphabet() { return alphabet_; }

template <int nTracks> const Alphabet &Tape<nTracks>::alphabet() const {
  return alphabet_;
}

template <int nTracks> int Tape<nTracks>::size() const noexcept {
  return mem_.size();
}

template <int nTracks> int Tape<nTracks>::numTracks() const noexcept {
  return nTracks;
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N == 1), int>>
const Symbol &Tape<nTracks>::peek() const {
  return at(tape_head_)[0];
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N == 1), int>>
Symbol &Tape<nTracks>::peek() {
  return at(tape_head_)[0];
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N > 1), int>>
const typename Tape<nTracks>::Column &Tape<nTracks>::peek() const {
  return at(tape_head_);
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N > 1), int>>
typename Tape<nTracks>::Column &Tape<nTracks>::peek() {
  return at(tape_head_);
}

template <int nTracks> void Tape<nTracks>::moveLeft() { --tape_head_; }

template <int nTracks> void Tape<nTracks>::moveRight() { ++tape_head_; }

template <int nTracks> void Tape<nTracks>::reset() {
  tape_head_ = 0;
  mem_.clear();
}

template <int nTracks>
void Tape<nTracks>::setInputString(const std::string &input_str) {
  reset();

  std::stringstream line_stream(input_str);
  std::string line;

  int row = 0;
  while (std::getline(line_stream, line) && row < nTracks) {

    std::vector<Symbol> symbols = alphabet_.splitInSymbols(line);

    for (int col = 0; col < symbols.size(); ++col) {
      at(col)[row] = symbols[col];
    }

    ++row;
  }
}

template <int nTracks>
const typename Tape<nTracks>::Column &Tape<nTracks>::at(int idx) const {
  // Fill with blanks
  if (!mem_.count(idx)) {
    mem_[idx].fill(alphabet_.blank());
  }

  return mem_.at(idx);
}

template <int nTracks>
typename Tape<nTracks>::Column &Tape<nTracks>::at(int idx) {
  const Tape<nTracks> &const_this = *this;
  return const_cast<Column &>(const_this.at(idx));
}

} // namespace turing
