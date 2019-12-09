#pragma once

#include <cstddef>
#include <tuple>
#include <vector>

namespace turing {

using Symbol = std::string;

class Utils {
public:
  static Symbol lambda;
  static Symbol blank;

  static std::vector<std::string> split(const std::string &str);

  static std::string &trim(std::string &str);
  static std::string &ltrim(std::string &str);
  static std::string &rtrim(std::string &str);

  static std::string nextLine(std::ifstream &file_stream);
};

template <size_t I, typename T> struct tuple_n {
  template <typename... Args>

  using type = typename tuple_n<I - 1, T>::template type<T, Args...>;
};

template <typename T> struct tuple_n<0, T> {
  template <typename... Args> using type = std::tuple<Args...>;
};

template <size_t I, typename T>
using tuple_of = typename tuple_n<I, T>::template type<>;

// Use: tuple_of<3, double> => "Tuple of 3 doubles"

} // namespace turing
