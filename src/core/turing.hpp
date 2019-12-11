#pragma once

#include "data/alphabet.hpp"
#include "state/state.hpp"
#include "utils/utils.hpp"

namespace turing {

class Turing {
public:
  Turing(int num_tapes = 1);
  ~Turing();

  int numTapes() const;
  void setNumTapes(int num_tapes);

  Alphabet& tapeAlphabet();
  const Alphabet& tapeAlphabet() const;

  Alphabet& inputAlphabet();
  const Alphabet& inputAlphabet() const;

  // States
  State* state(const std::string& name);
  bool hasState(const std::string& name) const;

  const State* initialState() const;
  void setInitialState(const std::string& name);

  void setFinalStates(const std::vector<std::string>& state_names);

  void addState(const std::string& s);
  void addStates(const std::vector<std::string>& names_str);

  // Transitions
  void addTransition(const std::string& transition_str);
  void addTransition(const std::string& initial_state_name,
                     const std::vector<Symbol>& input_symbols,
                     const std::string& end_state_name,
                     const std::vector<Symbol>& output_symbols,
                     const std::vector<Move>& moves);

  // Turing Machine
  bool debugMode() const;
  void toggleDebugMode(bool toggle);

  bool run(const std::string& input_string);
  bool run(State* current_state, std::vector<Tape>& tapes);

  friend std::ostream& operator<<(std::ostream& os, const Turing& turing);

private:
  Alphabet input_alphabet_;
  Alphabet tape_alphabet_;

  std::vector<Tape> tapes_;

  State* initial_state_{nullptr};
  std::map<std::string, State*> states_;

  bool debug_mode_{true};
};

}  // namespace turing
