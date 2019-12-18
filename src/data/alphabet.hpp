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

  bool contains(Symbol symbol) const;

  void addSymbol(Symbol symbol);
  void setSymbols(const std::vector<Symbol> &symbols);

  std::vector<Symbol> splitInSymbols(const std::string &symbols_str) const;

  friend std::ostream &operator<<(std::ostream &os, const Alphabet &alphabet);

private:
  std::string regexStr() const;

private:
  std::string blank_{"."};

  std::regex regex_;
  std::unordered_set<Symbol> alphabet_symbols_{blank_};
};

}  // namespace turing
