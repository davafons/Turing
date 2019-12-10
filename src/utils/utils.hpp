#pragma once

#include <cstddef>
#include <tuple>
#include <vector>

namespace turing {

using Symbol = std::string;
using Cell = std::vector<Symbol>;

class Utils {
public:
  static Symbol blank;

  static std::vector<std::string> split(const std::string &str);

  static std::string &trim(std::string &str);
  static std::string &ltrim(std::string &str);
  static std::string &rtrim(std::string &str);

  static std::string nextLine(std::ifstream &file_stream);
};

}  // namespace turing
