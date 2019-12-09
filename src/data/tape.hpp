#pragma once

#include <iostream>
#include <sstream>
#include <unordered_map>

#include "data/alphabet.hpp"
#include "utils/utils.hpp"

namespace turing {

template <int nTracks>
class Tape {
public:
  using Cell = std::array<Symbol, nTracks>;

public:
  explicit Tape(const std::string &input_str = "",
                const std::string &alphabet_str = "");

  Alphabet &alphabet();
  const Alphabet &alphabet() const;

  int numTracks() const noexcept;

  template <int N = nTracks, typename std::enable_if_t<(N == 1), int> = 0>
  Symbol peek() const;

  template <int N = nTracks, typename std::enable_if_t<(N > 1), int> = 0>
  Cell peek() const;

  template <int N = nTracks, typename std::enable_if_t<(N == 1), int> = 0>
  void write(Symbol symbol);

  void write(Cell cell);

  void moveLeft();
  void moveRight();

  void reset();

  void setInputString(const std::string &input_str);

private:
  int tape_head_{0};

  std::unordered_map<int, Cell> mem_;

  Alphabet alphabet_;
};

template <int nTracks>
Tape<nTracks>::Tape(const std::string &input_str, const std::string &alphabet_str) {
  if (alphabet_str.empty()) {
    alphabet_.addSymbols(input_str);
  } else {
    alphabet_.addSymbols(alphabet_str);
  }

  setInputString(input_str);
}

template <int nTracks>
Alphabet &Tape<nTracks>::alphabet() {
  return alphabet_;
}

template <int nTracks>
const Alphabet &Tape<nTracks>::alphabet() const {
  return alphabet_;
}

template <int nTracks>
int Tape<nTracks>::numTracks() const noexcept {
  return nTracks;
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N == 1), int>>
Symbol Tape<nTracks>::peek() const {
  if (!mem_.count(tape_head_)) {
    return alphabet_.blank();
  }

  return mem_.at(tape_head_)[0];
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N > 1), int>>
typename Tape<nTracks>::Cell Tape<nTracks>::peek() const {
  if (!mem_.count(tape_head_)) {
    Cell cell;
    cell.fill(alphabet_.blank());
    return cell;
  }

  return mem_.at(tape_head_);
}

template <int nTracks>
template <int N, typename std::enable_if_t<(N == 1), int>>
void Tape<nTracks>::write(Symbol symbol) {
  auto symbols = alphabet_.splitInSymbols(symbol);

  if (!alphabet_.contains(symbol)) {
    throw std::runtime_error("Can't write Symbol " + symbol + ". Not in Alphabet.");
  }

  mem_[tape_head_][0] = symbol;
}

template <int nTracks>
void Tape<nTracks>::write(Cell cell) {
  for (const auto &s : cell) {
    if (!alphabet_.contains(s) && s != alphabet_.blank()) {
      throw std::runtime_error("Can't write Symbol " + s + ". Not in Alphabet.");
    }
  }

  mem_[tape_head_] = cell;
}

template <int nTracks>
void Tape<nTracks>::moveLeft() {
  --tape_head_;
}

template <int nTracks>
void Tape<nTracks>::moveRight() {
  ++tape_head_;
}

template <int nTracks>
void Tape<nTracks>::reset() {
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
      if (!mem_.count(col)) {
        Cell cell;
        cell.fill(alphabet_.blank());
        mem_[col] = cell;
      }

      mem_[col][row] = symbols[col];
    }

    ++row;
  }
}

}  // namespace turing
