#pragma once

#include <iostream>
#include <sstream>
#include <unordered_map>

#include "data/alphabet.hpp"
#include "utils/utils.hpp"

namespace turing {

enum class Move { Left, Right, Stop };

class Tape {
public:
  explicit Tape(int rows = 1, const std::string &input_str = "",
                const std::string &alphabet_str = "");

  Alphabet &alphabet();
  const Alphabet &alphabet() const;

  int rows() const;

  Cell peek() const;
  void write(Cell cell);

  void move(Move dir);

  void reset();

  // void setInputString(const std::string &input_str);

private:
  int tape_head_{0};
  int rows_{0};

  std::unordered_map<int, Cell> data_;

  Alphabet alphabet_;
};

// template <int nTracks>
// void Tape<nTracks>::setInputString(const std::string &input_str) {
//   reset();
//
//   std::stringstream line_stream(input_str);
//   std::string line;
//
//   int row = 0;
//   while (std::getline(line_stream, line) && row < nTracks) {
//     std::vector<Symbol> symbols = alphabet_.splitInSymbols(line);
//
//     for (int col = 0; col < symbols.size(); ++col) {
//       if (!mem_.count(col)) {
//         Cell cell;
//         cell.fill(alphabet_.blank());
//         mem_[col] = cell;
//       }
//
//       mem_[col][row] = symbols[col];
//     }
//
//     ++row;
//   }
// }

}  // namespace turing
