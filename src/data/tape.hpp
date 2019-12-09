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

  Column peek() const;
  void moveLeft();
  void moveRight();

  void reset();

  void setInputString(const std::string &input_str);

  // TODO: Add Alphabet

  template <int N>
  friend std::ostream &operator<<(std::ostream &os, const Tape<N> &tape);

private:
  int tape_head_{0};

  std::unordered_map<int, Column> mem_;

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

template <int nTracks> int Tape<nTracks>::size() const noexcept {
  return mem_.size();
}

template <int nTracks> int Tape<nTracks>::numTracks() const noexcept {
  return nTracks;
}

template <int nTracks>
typename Tape<nTracks>::Column Tape<nTracks>::peek() const {
  if (!mem_.count(tape_head_)) {
    Column col{nTracks};
    col.fill(alphabet_.blank());

    return col;
  }

  return mem_[tape_head_];
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

  int track_num = 0;
  while (std::getline(line_stream, line)) {
    std::vector<Symbol> symbols = alphabet_.splitInSymbols(line);

    for (int i = 0; i < symbols.size(); ++i) {
      mem_[i][track_num] = symbols[i];
    }

    ++track_num;
  }
}

} // namespace turing
