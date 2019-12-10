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
Transition::Transition(const Cell& input_symbols, State* next_state,
                       const Cell& output_symbols, const Move& movement)

    : input_symbols_(input_symbols),
      next_state_(next_state),
      output_symbols_(output_symbols),
      movement_(movement) {}

/*!
 *  Symbol needed by the tape for the transition.
 */
Cell Transition::inputSymbols() const { return input_symbols_; }

/*!
 *  Symbols written to the stack when transitioning.
 */
Cell Transition::outputSymbols() const { return output_symbols_; }

/*!
 *  Movement done by the Tape upon transitioning.
 */
Move Transition::movement() const { return movement_; }

/*!
 *  Name of the next state to transition.
 */
std::string Transition::nextStateName() const {
  return (next_state_) ? next_state_->name() : "";
}

/*!
 *  Move to the next state and return it, modifying the tape and the stack on the
 *  process.
 */
State* Transition::nextState(Tape& current_tape) const {
  if (current_tape.peek() != input_symbols_) {
    return nullptr;
  }

  current_tape.write(output_symbols_);
  current_tape.move(movement_);

  return next_state_;
}

/*!
 *  Check if two transitions are equal.
 *  Note: For two transitions to be equal, they must have the same symbols, and point to
 *  the same "next_state_" objet.
 */
bool Transition::operator==(const Transition& other) const {
  return input_symbols_ == other.input_symbols_ &&
         output_symbols_ == other.output_symbols_ &&
         nextStateName() == other.nextStateName() && movement_ == other.movement_;
}

/*!
 *  Return the Transition as a string.
 */
std::string Transition::str() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

/*!
 *  Print the transition.
 */
std::ostream& operator<<(std::ostream& os, const Transition& t) {
  // os << "(" << t.input_symbol_ << ", " << t.stack_symbol_ << ") => {"
  //    << t.next_state_->name() << ", " << t.new_stack_symbols_ << "}";
  //
  os << "( ";

  for (const auto& s : t.input_symbols_) {
    os << s << ", ";
  }

  os << "\b\b ) => { " << t.nextStateName() << ", ";

  for (const auto& s : t.output_symbols_) {
    os << s << ", ";
  }

  // TODO: Change int to enum correct value
  os << to_string(t.movement()) << " }";

  return os;
}

}  // namespace turing
