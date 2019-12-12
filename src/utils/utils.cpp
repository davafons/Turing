#include "utils.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "data/tape.hpp"

namespace turing {

/*!
 *  Return the corresponding string for a Move enum
 */
std::string to_string(const Move &move) {
  switch (move) {
    case Move::Left:
      return "Left";
      break;

    case Move::Right:
      return "Right";
      break;

    case Move::Stop:
      return "Stop";
      break;

    default:
      return std::to_string(int(move));
  }
}

/*!
 *  Transform the string to a Move enum.
 *  Case insensitive.
 */
Move to_Move(std::string move_str) {
  std::transform(move_str.begin(), move_str.end(), move_str.begin(), ::tolower);
  if (move_str == "left" || move_str == "l") {
    return Move::Left;
  }

  if (move_str == "right" || move_str == "r") {
    return Move::Right;
  }

  if (move_str == "stop" || move_str == "s") {
    return Move::Stop;
  }

  return Move::Stop;
}

/*!
 *  Output operator for a vector of Symbols (std::strings).
 */
std::ostream &operator<<(std::ostream &os, const std::vector<Symbol> &symbols) {
  if (symbols.empty()) {
    os << "[ (empty) ]";
    return os;
  }

  os << "[";
  for (const auto &symbol : symbols) {
    os << symbol << ", ";
  }

  os << "\b\b]";

  return os;
}

/*!
 *  \class Utils
 *  \brief Utility methods and objects.
 */

/*!
 *  Symbol used to represent "blank".
 */
Symbol Utils::blank = "b";

/*!
 *  Split a string using whitespaces as delimiter.
 */
std::vector<std::string> Utils::split(const std::string &str, char delimiter) {
  std::vector<Symbol> result;

  std::stringstream symbols_stream(str);

  Symbol symbol;
  while (std::getline(symbols_stream, symbol, delimiter)) {
    symbol = Utils::trim(symbol);
    if (!symbol.empty()) {
      result.push_back(symbol);
    }
  }
  return result;
}

/*!
 *  Remove all whitespaces at the start and end of the string.
 */
std::string &Utils::trim(std::string &str) {
  return ltrim(rtrim(str));
}

/*!
 *  Remove all whitespaces at the start of the string.
 */
std::string &Utils::ltrim(std::string &str) {
  auto it = std::find_if_not(str.begin(), str.end(), ::isspace);
  str.erase(str.begin(), it);
  return str;
}

/*!
 *  Remove all whitespaces at the end of the string.
 */
std::string &Utils::rtrim(std::string &str) {
  auto it = std::find_if_not(str.rbegin(), str.rend(), ::isspace);
  str.erase(it.base(), str.end());
  return str;
}

/*!
 *  Read next line until its not empty or is not a comment.
 */
std::string Utils::nextLine(std::ifstream &file_stream) {
  std::string line;
  do {
    std::getline(file_stream, line);
  } while (!file_stream.eof() && (line.empty() || Utils::trim(line)[0] == '#'));

  return line;
}

}  // namespace turing
