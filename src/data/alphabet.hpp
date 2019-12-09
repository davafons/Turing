#pragma once

#include <regex>
#include <string>
#include <vector>

#include "utils/utils.hpp"

namespace turing {

class Alphabet {
public:
  Alphabet() = default;

  bool empty() const noexcept;
  size_t size() const noexcept;

  void reset();

  void addSymbol(Symbol symbol);
  void addSymbols(const std::string &symbols_str);

  std::vector<Symbol> splitInSymbols(const std::string &symbols_str);

  friend std::ostream &operator<<(std::ostream &os, const Alphabet &alphabet);

private:
  std::string regex_str_{"\\" + Utils::lambda};
  std::regex regex_;

  size_t size_{0};
};

} // namespace turing
