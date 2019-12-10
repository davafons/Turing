#include <iostream>

#include "core/turing.hpp"

int main() {
  turing::Turing machine;

  machine.addStates({"q0", "q1", "q2"});
  machine.inputAlphabet().addSymbols({"0", "1"});
  machine.tapeAlphabet().addSymbols({"0", "1", "."});

  machine.set

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

  tape.setInputString("ab.a\nb.aa");

  std::cout << tape << std::endl;

  return 0;
}
