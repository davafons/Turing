#pragma once

#include <functional>
#include <string>
#include <vector>

#include "data/tape.hpp"
#include "utils/utils.hpp"

namespace turing {

class State;

class Transition {
public:
  Transition() = default;
  Transition(const Cell& input_symbols, const Cell& output_symbols, State* next_state,
             const Move& dir);

  Cell inputSymbols() const;
  Cell outputSymbols() const;

  Move movement() const;

  std::string nextStateName() const;

  State* nextState(Tape& current_tape) const;

  std::string str() const;

  bool operator==(const Transition& other) const;

  friend std::ostream& operator<<(std::ostream& os, const Transition& t);

private:
  Cell input_symbols_{};
  State* next_state_{nullptr};
  Cell output_symbols_{};
  Move movement_{Move::Stop};
};

}  // namespace turing

/*!
 *  Hash function. Used to insert Transition elements on an "unordered_set"
 */
namespace std {
template <>
struct hash<turing::Transition> {
  size_t operator()(const turing::Transition& obj) const {
    return hash<std::string>()(obj.str());
  }
};

}  // namespace std
