#include <iostream>

#include "core/turing.hpp"

int main() {
  turing::Turing machine;

  machine.addStates({"q0", "q1", "q2"});
  machine.inputAlphabet().addSymbols({"0", "1"});
  machine.tapeAlphabet().addSymbols({"0", "1", "."});

  machine.setInitialState("q0");
  machine.tapeAlphabet().setBlank(".");

  machine.setFinalStates({"q2"});

  machine.addTransition("q0", {"0"}, "q1", {"0"}, turing::Move::Right);
  machine.addTransition("q0", {"1"}, "q0", {"1"}, turing::Move::Right);
  machine.addTransition("q1", {"0"}, "q0", {"0"}, turing::Move::Right);
  machine.addTransition("q1", {"1"}, "q1", {"1"}, turing::Move::Right);
  machine.addTransition("q1", {"."}, "q2", {"."}, turing::Move::Right);

  // tape.write({"a", "b"});
  //
  // tape.move(turing::Move::Right);
  // tape.move(turing::Move::Right);
  //
  // tape.write({"b", "a"});
  //
  // tape.move(turing::Move::Right);
  // tape.move(turing::Move::Right);
  // tape.move(turing::Move::Right);
  //
  // tape.write({"a", "a"});

  std::cout << machine << std::endl;

  return 0;
}
