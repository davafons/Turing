#include <iostream>

#include "data/tape.hpp"
#include "state/state.hpp"

int main() {
  auto *q1 = new turing::State("q1");
  auto *q2 = new turing::State("q2");

  q1->addTransition(turing::Transition({"0"}, q2, {"1"}, turing::Move::Right));
  q1->addTransition(turing::Transition({"0"}, q2, {"1"}, turing::Move::Right));

  q2->addTransition(turing::Transition({"1"}, q1, {"0"}, turing::Move::Left));
  q2->addTransition(turing::Transition({"1"}, q2, {"0"}, turing::Move::Right));

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
  tape.alphabet().addSymbols({"a", "d", "c"});

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

  std::cout << "--- Movement example ---" << std::endl;
  turing::Tape mov_tape(1);
  mov_tape.alphabet().addSymbols({"0", "1"});
  mov_tape.setInputString({{"0"}});
  auto *new_state = q1->transitions({"0"}).begin()->nextState(mov_tape);

  std::cout << new_state->name() << std::endl;

  return 0;
}
