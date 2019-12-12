#include "turing.hpp"

#include <sstream>

#include "state/transition.hpp"

namespace turing {

Turing::Turing(int num_tapes) {
  setNumTapes(num_tapes);
}

Turing::~Turing() {
  for (const auto& s : states_) {
    delete s.second;
  }
}

int Turing::numTapes() const {
  return tapes_.size();
}

void Turing::setNumTapes(int num_tapes) {
  tapes_ = std::vector<Tape>(num_tapes, Tape(tape_alphabet_));
}

Alphabet& Turing::tapeAlphabet() {
  return tape_alphabet_;
}

const Alphabet& Turing::tapeAlphabet() const {
  return tape_alphabet_;
}

Alphabet& Turing::inputAlphabet() {
  return input_alphabet_;
}

const Alphabet& Turing::inputAlphabet() const {
  return input_alphabet_;
}

State* Turing::state(const std::string& name) {
  try {
    return states_.at(name);
  } catch (const std::out_of_range& e) {
    throw std::runtime_error("> ERROR: State " + name + " is not defined.");
  }
}

bool Turing::hasState(const std::string& name) const {
  return states_.count(name);
}

const State* Turing::initialState() const {
  return initial_state_;
}

void Turing::setInitialState(const std::string& name) {
  if (name.empty()) {
    initial_state_ = nullptr;
  } else {
    initial_state_ = state(name);
  }
}

void Turing::setFinalStates(const std::vector<std::string>& state_names) {
  // First, reset all states to non-final.
  for (const auto& state : states_) {
    state.second->setFinal(false);
  }

  for (const auto& name : state_names) {
    state(name)->setFinal(true);
  }
}

void Turing::addState(const std::string& name) {
  if (name.empty()) {
    return;
  }

  if (states_.count(name)) {
    std::cerr << "> WARNING: A state with name \"" << name
              << "\" already exists. The state WILL NOT be replaced." << std::endl;
  } else {
    states_[name] = new State(name);
  }
}

void Turing::addStates(const std::vector<std::string>& state_names) {
  for (const auto& name : state_names) {
    addState(name);
  }
}

void Turing::addTransition(const std::string& transition_str) {
  std::stringstream transition_stream(transition_str);

  std::string initial_state_name;
  transition_stream >> initial_state_name;

  std::vector<Symbol> input_symbols;
  for (int i = 0; i < numTapes(); ++i) {
    std::string symbol;
    transition_stream >> symbol;
    input_symbols.push_back(symbol);
  }

  std::string end_state_name;
  transition_stream >> end_state_name;

  std::vector<Symbol> output_symbols;
  for (int i = 0; i < numTapes(); ++i) {
    std::string symbol;
    transition_stream >> symbol;
    output_symbols.push_back(symbol);
  }

  std::vector<Move> moves;

  std::string move_str;
  while (std::getline(transition_stream, move_str)) {
    for (const auto& m : Utils::split(move_str, ' ')) {
      moves.push_back(to_Move(m));
    }
  }

  addTransition(
      initial_state_name, input_symbols, end_state_name, output_symbols, moves);
}

void Turing::addTransition(const std::string& initial_state_name,
                           const std::vector<Symbol>& input_symbols,
                           const std::string& end_state_name,
                           const std::vector<Symbol>& output_symbols,
                           const std::vector<Move>& moves) {

  state(initial_state_name)
      ->addTransition(
          Transition(input_symbols, state(end_state_name), output_symbols, moves));
}

// Turing Machine
bool Turing::debugMode() const {
  return debug_mode_;
}
void Turing::toggleDebugMode(bool toggle) {
  debug_mode_ = toggle;
}

bool Turing::run(const std::string& input_string) {
  // Fill initial tape with input string
  tapes_[0].setInputString(input_string);

  State* current_state = initial_state_;

  return run(current_state, tapes_);
}

bool Turing::run(State* current_state, std::vector<Tape>& tapes) {
  // Exit if the current state is null
  if (!current_state) {
    return false;
  }

  // Helper function to print the state of the Turing machine
  auto print_turing = [&current_state, &tapes] {
    std::cout << "---------------------------" << std::endl;
    std::cout << "Current state: " << current_state->name() << std::endl;
    std::cout << tapes;
    std::cout << "---------------------------" << std::endl;
  };

  // Return true if the Turing machine arrived a Final state
  if (current_state->isFinal()) {
    if (debugMode()) {
      print_turing();
      std::cout << "> " << current_state->name() << " is a Final state." << std::endl;
      std::cout << "---------------------------" << std::endl;
    }

    return true;
  }

  if (debugMode()) {
    print_turing();
  }

  // Collect all symbols from all tapes for each current head
  std::vector<Symbol> input_symbols;
  for (const auto& tape : tapes) {
    input_symbols.push_back(tape.peek());
  }

  // Explore transitions for the current tape symbols.
  for (const auto& transition : current_state->transitions(input_symbols)) {
    if (debugMode()) {
      std::cout << "> Transition: " << transition << std::endl;
    }

    // For each transition, clone the tapes and call this run method recursively.
    std::vector<Tape> new_tapes(tapes);
    State* new_state = transition.nextState(new_tapes);

    // Check if by exploring this transition the Turing machine can accept the string.
    bool result = run(new_state, new_tapes);

    // If the string is accepted, return true to stop execution.
    if (result) {
      return true;
    }

    // Otherwise, explore the other transitions
    if (debugMode()) {
      std::cout << ">> Can't continue. Going back to previous state." << std::endl;
      print_turing();
    }
  }

  // If all the transitions have been explored, but we still aren't on a final state,
  // just return false
  return false;
}

std::ostream& operator<<(std::ostream& os, const Turing& machine) {
  os << "> Turing machine: " << machine.numTapes() << " tapes." << std::endl;
  os << "> States: ";

  for (const auto& s : machine.states_) {
    os << s.second->name() << ((s.second->isFinal()) ? "*" : "") << " ";
  }

  os << std::endl;

  os << "> Input alphabet: " << machine.inputAlphabet() << std::endl;
  os << "> Tape alphabet: " << machine.tapeAlphabet() << std::endl;

  os << "> Initial state: " << machine.initial_state_->name() << std::endl;

  os << "> Tapes:\n" << machine.tapes_;

  os << "> Transitions: " << std::endl;
  for (const auto& s_pair : machine.states_) {
    std::cout << *s_pair.second << std::endl;
  }

  return os;
}

}  // namespace turing
