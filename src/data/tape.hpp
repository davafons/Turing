#pragma once

#include <iostream>
#include <map>
#include <sstream>

#include "data/alphabet.hpp"
#include "utils/utils.hpp"

namespace turing {

class Tape {
public:
  explicit Tape(const Alphabet &alphabet = Alphabet(), int num_tracks = 1);

  const Alphabet &alphabet() const;

  bool empty() const;

  int numTracks() const;

  Cell peek() const;
  void write(Cell cell);

  void move(Move dir);

  void reset();

  void setInputString(const std::string &input_string);

  friend std::ostream &operator<<(std::ostream &os, const Tape &tape);

private:
  Cell at(int idx) const;

private:
  int tape_head_{0};
  int num_tracks_{0};

  std::map<int, Cell> data_;

  const Alphabet &alphabet_;
};

}  // namespace turing
