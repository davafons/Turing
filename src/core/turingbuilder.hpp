#pragma once

#include "core/turing.hpp"

namespace turing {

class TuringBuilder {
public:
  static Turing fromFile(const std::string& file_path);
};

}  // namespace turing
