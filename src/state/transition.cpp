#include "transition.hpp"

#include "state/state.hpp"

namespace turing {

/*!
 *  \class Transition
 *  \brief Represents a transition to a new state.
 *
 *  Transition objects are inmutable.
 */

/*!
 *  Construct a new Transition object.
 */
Transition::Transition(const std::vector<Symbol>& input_symbols,
                       State* next_state,
                       const std::vector<Symbol>& output_symbols,
                       const std::vector<Move>& moves)

    : input_symbols_(input_symbols),
      next_state_(next_state),
      output_symbols_(output_symbols),
      moves_(moves) {}

/*!
 *  Symbol needed by the Tape(s) for the transition.
 */
std::vector<Symbol> Transition::inputSymbols() const {
  return input_symbols_;
}

/*!
 *  Symbols written to the Tape(s) when transitioning.
 */
std::vector<Symbol> Transition::outputSymbols() const {
  return output_symbols_;
}

/*!
 *  Movement done by the Tape(s) upon transitioning.
 */
std::vector<Move> Transition::moves() const {
  return moves_;
}

/*!
 *  Name of the next state to which transition.
 */
std::string Transition::nextStateName() const {
  return (next_state_) ? next_state_->name() : "";
}

/*!
 *  Move to the next state and return it, modifying the Tape(s) on the process.
 *  If the transition couldn't be performed, return null.
 */
State* Transition::nextState(std::vector<Tape>& tapes) const {
  // Must have the same amout of symbols that tapes (To write on each one)
  if (tapes.size() != input_symbols_.size()) {
    return nullptr;
  }

  // Check that all tapes point to the correct symbol
  for (size_t i = 0; i < tapes.size(); ++i) {
    // Input symbols must be the same
    if (tapes[i].peek() != input_symbols_[i]) {
      return nullptr;
    }
  }

  // Write on tapes
  for (size_t i = 0; i < tapes.size(); ++i) {
    tapes[i].write(output_symbols_[i]);
    tapes[i].move((moves_.size() == 1) ? moves_[0] : moves_[i]);
  }

  return next_state_;
}

/*!
 *  Check if two transitions are equal.
 *  Note: For two transitions to be equal, they must have the same symbols, movements,
 *  and point to the same state.
 */
bool Transition::operator==(const Transition& other) const {
  return input_symbols_ == other.input_symbols_ &&
         output_symbols_ == other.output_symbols_ &&
         nextStateName() == other.nextStateName() && moves_ == other.moves_;
}

/*!
 *  Return the Transition as a string.
 */
std::string to_string(const Transition& other) {
  std::stringstream ss;
  ss << other;
  return ss.str();
}

/*!
 *  Print the transition.
 */
std::ostream& operator<<(std::ostream& os, const Transition& t) {
  // os << "(" << t.input_symbol_ << ", " << t.stack_symbol_ << ") => {"
  //    << t.next_state_->name() << ", " << t.new_stack_symbols_ << "}";
  //
  os << t.input_symbols_ << " => { " << t.nextStateName() << ", " << t.output_symbols_
     << ", ";

  for (const auto& mov : t.moves_) {
    os << "[" << to_string(mov) << "]";
  }

  os << " }";

  return os;
}

}  // namespace turing
