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
  Transition(const std::vector<Symbol>& input_symbols,
             State* next_state,
             const std::vector<Symbol>& output_symbols,
             const std::vector<Move>& moves);

  std::vector<Symbol> inputSymbols() const;
  std::vector<Symbol> outputSymbols() const;

  std::vector<Move> moves() const;

  std::string nextStateName() const;

  State* nextState(std::vector<Tape>& tapes) const;

  friend std::string to_string(const Transition& other);

  bool operator==(const Transition& other) const;

  friend std::ostream& operator<<(std::ostream& os, const Transition& t);

private:
  std::vector<Symbol> input_symbols_{};
  State* next_state_{nullptr};
  std::vector<Symbol> output_symbols_{};
  std::vector<Move> moves_{Move::Stop};
};

}  // namespace turing

/*!
 *  Hash function. Used to insert Transition elements on an "unordered_set"
 */
namespace std {
template <>
struct hash<turing::Transition> {
  size_t operator()(const turing::Transition& obj) const {
    return hash<std::string>()(to_string(obj));
  }
};

}  // namespace std
