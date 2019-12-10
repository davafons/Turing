#include "utils.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace turing {

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
std::vector<std::string> Utils::split(const std::string &str) {
  std::vector<Symbol> result;

  std::stringstream symbols_stream(str);

  Symbol symbol;
  while (symbols_stream >> symbol) {
    result.push_back(symbol);
  }

  return result;
}

/*!
 *  Remove all whitespaces at the start and end of the string.
 */
std::string &Utils::trim(std::string &str) { return ltrim(rtrim(str)); }

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
