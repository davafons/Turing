#include <iostream>

#include "core/turing.hpp"

int main() {
  turing::Turing machine;

  machine.addState("q1");
  machine.addState("q2");
  machine.addState("q3");

  turing::Alphabet alpha;
  alpha.addSymbols({"a", "b"});

  turing::Tape tape(alpha, 2);

  tape.write({"a", "b"});

  tape.move(turing::Move::Right);
  tape.move(turing::Move::Right);

  tape.write({"b", "a"});

  tape.move(turing::Move::Right);
  tape.move(turing::Move::Right);
  tape.move(turing::Move::Right);

  tape.write({"a", "a"});

  std::cout << tape << std::endl;

  return 0;
}
