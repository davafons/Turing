#pragma once

#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils/utils.hpp"

namespace turing {

class Alphabet {
public:
  Alphabet() = default;

  bool empty() const noexcept;
  size_t size() const noexcept;

  Symbol blank() const noexcept;
  void setBlank(Symbol blank);

  void reset();

  bool contains(Symbol symbol);

  void addSymbol(Symbol symbol);
  void addSymbols(const std::string &symbols_str);

  std::vector<Symbol> splitInSymbols(const std::string &symbols_str);

  friend std::ostream &operator<<(std::ostream &os, const Alphabet &alphabet);

private:
  std::string regexStr() const;

private:
  std::string blank_{"b"};

  std::regex regex_;
  std::unordered_set<Symbol> alphabet_symbols_;
};

} // namespace turing
