#include "state.hpp"

#include <iostream>

namespace turing {

/*!
 *  \class State
 *  \brief Class representing a State with transitions.
 */

/*!
 *  Construct a new state object. MUST have a name.
 */
State::State(const std::string &name) : name_(name) {
  if (name_.empty()) {
    throw std::runtime_error("Can't create a state with empty name!");
  }
}

/*!
 *  Return the State name.
 */
std::string State::name() const {
  return name_;
}

/*!
 *  Return if the state is final.
 */
bool State::isFinal() const {
  return final_;
}

/*!
 *  Set if the state is final.
 */
void State::setFinal(bool f) {
  final_ = f;
}

/*!
 *  Return all the transitions associated to these input and stack symbols.
 *  If there aren't any transitions for the symbols, return an empty set.
 */
std::unordered_set<Transition> &State::transitions(
    const std::vector<Symbol> &input_symbols) {
  return transitions_[input_symbols];
}

/*!
 *  Add a new transition from the state.
 *  Note: All transitions are guaranteed to be unique. Can't add two equal
 * transitions.
 */
void State::addTransition(const Transition &transition) {
  transitions_[transition.inputSymbols()].insert(transition);
}

/*!
 *  Print the State name and its transitions.
 */
std::ostream &operator<<(std::ostream &os, const State &state) {
  for (const auto &t_pair : state.transitions_) {
    os << state.name() << ": [ ";
    for (const auto &t : t_pair.second) {
      os << t << ", ";
    }
    os << "\b\b ]" << std::endl;
  }
  return os;
}

}  // namespace turing
