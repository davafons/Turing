#include "turing.hpp"

#include <sstream>

#include "state/transition.hpp"

namespace turing {

Turing::Turing(int num_tapes, int num_tracks) {
  tapes_ = std::vector<Tape>(num_tapes, Tape(tape_alphabet_, num_tracks));
}

Turing::~Turing() {
  for (const auto& s : states_) {
    delete s.second;
  }
}

int Turing::numTapes() const {
  return tapes_.size();
}

int Turing::numTracks() const {
  return tape_tracks_;
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

bool Turing::hasState(const std::string& name) {
  return states_.count(name);
}

const State* Turing::startState() const {
  return start_state_;
}

void Turing::setInitialState(const std::string& name) {
  if (name.empty()) {
    start_state_ = nullptr;
  } else {
    start_state_ = state(name);
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

void Turing::addTransition(const std::string& start_state_name,
                           const Cell& input_symbols,
                           const std::string& end_state_name,
                           const Cell& output_symbols,
                           const Move& movement) {

  state(start_state_name)
      ->addTransition(
          Transition(input_symbols, state(end_state_name), output_symbols, movement));
}

// Turing Machine
bool Turing::debugMode() const {
  return debug_mode_;
}
void Turing::toggleDebugMode(bool toggle) {
  debug_mode_ = toggle;
}

bool Turing::run(const std::string& input_string) {
  // Split input string, fill tape with symbols

  tapes_[0].setInputString(input_string);

  return true;
}

std::ostream& operator<<(std::ostream& os, const Turing& machine) {
  os << "> Turing machine: " << machine.numTapes() << " tapes / " << machine.numTracks()
     << " tracks." << std::endl;

  os << "> States: ";

  for (const auto& s : machine.states_) {
    os << s.second->name() << ((s.second->isFinal()) ? "*" : "") << " ";
  }

  os << std::endl;

  os << "> Input alphabet: " << machine.inputAlphabet() << std::endl;
  os << "> Tape alphabet: " << machine.tapeAlphabet() << std::endl;

  os << "> Initial state: " << machine.start_state_->name() << std::endl;

  os << "> Tapes:\n";

  for (int i = 0; i < machine.tapes_.size(); ++i) {
    os << "Tape " << i << std::endl;
    os << machine.tapes_[i] << std::endl;
  }

  os << std::endl;

  os << "> Transitions: " << std::endl;
  for (const auto& s_pair : machine.states_) {
    std::cout << *s_pair.second << std::endl;
  }

  return os;
}

}  // namespace turing
