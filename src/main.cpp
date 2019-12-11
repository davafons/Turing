#include <iomanip>
#include <iostream>

#include "core/turing.hpp"
#include "core/turingbuilder.hpp"

int main() {
  turing::Turing machine = turing::TuringBuilder::fromFile("examples/Ejemplo_MT.txt");
  std::cout << machine << std::endl;

  std::string input_string = "00100";
  bool result = machine.run(input_string);

  std::cout << "String " << input_string << ": " << std::boolalpha << result
            << std::endl;

  return 0;
}
