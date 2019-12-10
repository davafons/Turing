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

  auto print = [](const auto &col) {
    std::cout << "Col: [";
    for (const auto &value : col) {
      std::cout << value << ", ";
    }
    std::cout << "\b\b]\n";
  };

  turing::Tape tape(3);
  tape.alphabet().addSymbols("a d c");

  print(tape.peek());
  tape.write({"a", "d", "b"});

  print(tape.peek());

  std::vector<turing::Cell> input_string = {
      {"a", "b", "c"}, {"a", "a", "a"}, {"d", "b", "b"}};

  tape.setInputString(input_string);

  std::cout << "----" << std::endl;
  print(tape.peek());
  tape.move(turing::Move::Right);
  print(tape.peek());
  tape.move(turing::Move::Right);
  print(tape.peek());
  tape.move(turing::Move::Right);
  print(tape.peek());

  return 0;
}
