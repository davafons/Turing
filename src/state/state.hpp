#pragma once

#include <map>
#include <string>
#include <unordered_set>

#include "state/transition.hpp"
#include "utils/utils.hpp"

namespace turing {

class State {
public:
  explicit State(const std::string &name);

  std::string name() const;

  bool isFinal() const;
  void setFinal(bool f);

  std::unordered_set<Transition> &transitions(const Cell &input_symbols);
  void addTransition(const Transition &transition);

  friend std::ostream &operator<<(std::ostream &os, const State &state);

private:
  const std::string name_;
  bool final_{false};

  std::map<Cell, std::unordered_set<Transition>> transitions_;
};

}  // namespace turing
