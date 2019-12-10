#pragma once

#include <iostream>
#include <map>
#include <sstream>

#include "data/alphabet.hpp"
#include "utils/utils.hpp"

namespace turing {

class Tape {
public:
  explicit Tape(const Alphabet &alphabet = Alphabet());

  const Alphabet &alphabet() const;

  bool empty() const;

  Symbol peek() const;
  void write(Symbol symbol);

  void move(Move dir);

  void reset();

  void setInputString(const std::string &input_string);

  friend std::ostream &operator<<(std::ostream &os, const Tape &tape);

private:
  Symbol at(int idx) const;

private:
  int tape_head_{0};
  std::map<int, Symbol> data_;

  const Alphabet &alphabet_;
};

}  // namespace turing
