#pragma once

#include <iostream>
#include <tuple>
#include <vector>

namespace turing {

class Tape;

using Symbol = std::string;
using Cell = std::vector<Symbol>;

enum class Move { Left, Right, Stop };
std::string to_string(const Move& move);

std::ostream& operator<<(std::ostream& os, const Cell& cell);
std::ostream& operator<<(std::ostream& os, const std::vector<Cell>& cell);
std::ostream& operator<<(std::ostream& os, const std::vector<Tape>& tapes);

class Utils {
public:
  static Symbol blank;

  static std::vector<std::string> split(const std::string& str, char delimiter = '\n');

  static std::string& trim(std::string& str);
  static std::string& ltrim(std::string& str);
  static std::string& rtrim(std::string& str);

  static std::string nextLine(std::ifstream& file_stream);
};

}  // namespace turing
