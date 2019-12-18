#include "alphabet.hpp"

#include <iostream>

namespace turing {

/*!
 *  \class Alphabet
 *  \brief Set of symbols used for splitting strings.
 *
 *  Use this class to split a string by its recogizable symbols.
 *
 *  For example, for the following alphabet:
 *        A BC D
 *  The input string "ABCDFA" will be splitted in:
 *      [ A BC D A ]
 *
 *  (Note how unrecognized symbols like F are skipped)
 *  (Also, note how even if the string doesn't has spaces, the symbol BD is
 * recognized as a whole)
 *
 */

/*!
 *  Check if the alphabet is empty.
 */
bool Alphabet::empty() const noexcept {
  return alphabet_symbols_.empty();
}

/*!
 *  Return the size of the alphabet.
 */
size_t Alphabet::size() const noexcept {
  return alphabet_symbols_.size();
}

/*!
 *  Return the blank Symbol of the alphabet.
 */
Symbol Alphabet::blank() const noexcept {
  return blank_;
}

/*!
 *  Set a new blank Symbol to the alphabet.
 *  The blank symbol can't be a symbol already on the alphabet.
 */
void Alphabet::setBlank(Symbol blank) {
  if (blank == blank_) {
    return;
  }

  if (alphabet_symbols_.count(blank)) {
    std::cerr << "Can't set blank symbol to " << blank << ". Already in Alphabet."
              << std::endl;
  } else {
    // Remove last blank symbol
    alphabet_symbols_.erase(blank_);

    // Set new one
    blank_ = blank;
  }
}

/*!
 *  Remove all symbols from the alphabet.
 */
void Alphabet::reset() {
  alphabet_symbols_.clear();
  regex_ = std::regex();
}

/*!
 *  Check if the passed Symbol is in the alphabet.
 */
bool Alphabet::contains(Symbol symbol) const {
  return alphabet_symbols_.count(symbol);
}

/*!
 *  Add a new symbol to the Alphabet.
 */
void Alphabet::addSymbol(Symbol symbol) {
  if (!alphabet_symbols_.count(symbol)) {
    alphabet_symbols_.insert(symbol);

    regex_ = std::regex(regexStr());
  }
}

/*!
 *  Set a new set of symbols to the Alphabet.
 */
void Alphabet::setSymbols(const std::vector<Symbol> &symbols) {
  alphabet_symbols_.clear();

  for (const auto &symbol : symbols) {
    alphabet_symbols_.insert(symbol);
  }

  regex_ = std::regex(regexStr());
}

/*!
 *  Use the Alphabet to split the input symbol on a vector of individual
 * Symbols. Note: Unrecognized elements are skipped.
 */
std::vector<Symbol> Alphabet::splitInSymbols(const std::string &symbols_str) const {
  std::vector<Symbol> matches;

  // Prints a warning message if a symbol was skipped due to not being on the
  // Alphabet.
  auto check_sticky = [](int init_pos, int end_pos, const std::string &symbols_str) {
    if (init_pos != end_pos) {
      std::cout << "WARNING! Unrecognized symbol: "
                << symbols_str.substr(init_pos, end_pos - init_pos) << std::endl;
    }
  };

  int current_pos = 0;
  for (auto it = std::sregex_iterator(symbols_str.begin(), symbols_str.end(), regex_);
       it != std::sregex_iterator();
       ++it) {
    // Push the current match to the symbols vector
    matches.push_back(it->str());

    // Check if we skipped some symbol between matches
    check_sticky(current_pos, it->position(), symbols_str);
    current_pos = it->position() + it->length();
  }

  check_sticky(current_pos, symbols_str.length(), symbols_str);

  return matches;
}

/*!
 *  Print the content of the alphabet (Splitted by whitespaces)
 */
std::ostream &operator<<(std::ostream &os, const Alphabet &alphabet) {
  std::string alphabet_symbols(alphabet.regexStr());
  std::replace(alphabet_symbols.begin(), alphabet_symbols.end(), '|', ' ');
  std::replace(alphabet_symbols.begin(), alphabet_symbols.end(), '\\', ' ');

  os << alphabet_symbols;

  return os;
}

/*!
 *  Transform the alphabet symbols to a regex expression (string).
 */
std::string Alphabet::regexStr() const {
  std::string regex_str;

  regex_str += "(" + *alphabet_symbols_.cbegin() + ")";

  for (auto it = next(alphabet_symbols_.cbegin()); it != alphabet_symbols_.cend();
       ++it) {
    regex_str += "|(" + *it + ")";
  }

  std::cout << regex_str << std::endl;

  return regex_str;
}

}  // namespace turing
