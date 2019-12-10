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
  Transition(const std::vector<Cell>& input_symbols,
             State* next_state,
             const std::vector<Cell>& output_symbols,
             const std::vector<Move>& moves);

  std::vector<Cell> inputSymbols() const;
  std::vector<Cell> outputSymbols() const;

  std::vector<Move> moves() const;

  std::string nextStateName() const;

  State* nextState(std::vector<Tape>& tapes) const;

  std::string str() const;

  bool operator==(const Transition& other) const;

  friend std::ostream& operator<<(std::ostream& os, const Transition& t);

private:
  std::vector<Cell> input_symbols_{};
  State* next_state_{nullptr};
  std::vector<Cell> output_symbols_{};
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
    return hash<std::string>()(obj.str());
  }
};

}  // namespace std
