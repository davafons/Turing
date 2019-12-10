#include <iomanip>
#include <iostream>

#include "core/turing.hpp"

int main() {
  turing::Turing machine(1);

  machine.addStates({"q0", "q1", "q2"});
  machine.inputAlphabet().addSymbols({"0", "1"});
  machine.tapeAlphabet().addSymbols({"0", "1", "."});

  machine.setInitialState("q0");
  machine.tapeAlphabet().setBlank(".");

  machine.setFinalStates({"q2"});
  // Simple example
  machine.addTransition("q0", {{"0"}}, "q1", {{"0"}}, {turing::Move::Right});
  machine.addTransition("q0", {{"0"}}, "q1", {{"0"}}, {turing::Move::Right});
  machine.addTransition("q0", {{"0"}}, "q1", {{"0"}}, {turing::Move::Right});
  machine.addTransition("q0", {{"1"}}, "q0", {{"1"}}, {turing::Move::Right});
  machine.addTransition("q1", {{"0"}}, "q0", {{"0"}}, {turing::Move::Right});
  machine.addTransition("q1", {{"1"}}, "q1", {{"1"}}, {turing::Move::Right});
  machine.addTransition("q1", {{"."}}, "q2", {{"."}}, {turing::Move::Right});

  // Multi track example
  // machine.addTransition("q0", {{"0", "0"}}, "q1", {{"0", "1"}},
  // {turing::Move::Right}); machine.addTransition("q0", {{"0", "0"}}, "q1", {{"0",
  // "0"}}, {turing::Move::Right}); machine.addTransition("q0", {{"0", "1"}}, "q1",
  // {{"0", "0"}}, {turing::Move::Right}); machine.addTransition("q0", {{"1", "1"}},
  // "q0", {{"1", "."}}, {turing::Move::Right}); machine.addTransition("q1", {{"0",
  // "0"}}, "q0", {{"0", "."}}, {turing::Move::Right}); machine.addTransition("q1",
  // {{"1", "1"}}, "q1", {{"1", "1"}}, {turing::Move::Right});
  // machine.addTransition("q1", {{".", "."}}, "q2", {{".", "."}},
  // {turing::Move::Right});

  // // Multi tape example
  // machine.addTransition("q0",
  //                       {{"0"}, {"0"}},
  //                       "q1",
  //                       {{"0"}, {"1"}},
  //                       {turing::Move::Right, turing::Move::Left});
  // machine.addTransition("q0",
  //                       {{"0"}, {"1"}},
  //                       "q1",
  //                       {{"0"}, {"0"}},
  //                       {turing::Move::Right, turing::Move::Stop});
  // machine.addTransition("q0",
  //                       {{"1"}, {"."}},
  //                       "q0",
  //                       {{"1"}, {"1"}},
  //                       {turing::Move::Right, turing::Move::Stop});
  // machine.addTransition("q1",
  //                       {{"0"}, {"."}},
  //                       "q0",
  //                       {{"0"}, {"1"}},
  //                       {turing::Move::Right, turing::Move::Left});
  // machine.addTransition("q1",
  //                       {{"1"}, {"."}},
  //                       "q1",
  //                       {{"1"}, {"0"}},
  //                       {turing::Move::Right, turing::Move::Stop});
  // machine.addTransition("q1",
  //                       {{"."}, {"0"}},
  //                       "q2",
  //                       {{"."}, {"."}},
  //                       {turing::Move::Right, turing::Move::Stop});

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

  std::string input_string = "0010";
  bool result = machine.run(input_string);

  std::cout << "String " << input_string << " accepted: " << std::boolalpha << result
            << std::endl;

  return 0;
}
