#include <iostream>

#include "data/tape.hpp"
#include "state/state.hpp"

int main() {
  auto *q1 = new turing::State("q1");
  auto *q2 = new turing::State("q2");

  q1->addTransition(turing::Transition({"A"}, q2, {"B"}, turing::Move::Right));
  q1->addTransition(turing::Transition({"A"}, q2, {"B"}, turing::Move::Right));

  q2->addTransition(turing::Transition({"B"}, q1, {"A"}, turing::Move::Left));
  q2->addTransition(turing::Transition({"B"}, q2, {"C"}, turing::Move::Right));

  std::cout << *q1 << std::endl;
  std::cout << *q2 << std::endl;

  return 0;
}
