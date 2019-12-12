#include "turingbuilder.hpp"

#include <fstream>
#include <sstream>

namespace turing {

Turing TuringBuilder::fromFile(const std::string& file_path) {
  std::ifstream file_stream(file_path);
  if (!file_stream.is_open()) {
    throw std::runtime_error("Can't read Turing Machine file: " + file_path);
  }

  Turing machine;

  std::string line;
  try {
    // Number of tapes
    line = Utils::nextLine(file_stream);
    machine.setNumTapes(std::stoi(line));

    // States
    line = Utils::nextLine(file_stream);
    machine.addStates(Utils::split(line, ' '));

    // Input Alphabet
    line = Utils::nextLine(file_stream);
    machine.inputAlphabet().addSymbols(Utils::split(line, ' '));

    // Tape Alphabet
    line = Utils::nextLine(file_stream);
    machine.tapeAlphabet().addSymbols(Utils::split(line, ' '));

    // Initial State
    line = Utils::nextLine(file_stream);
    machine.setInitialState(line);

    // Blank symbol
    line = Utils::nextLine(file_stream);
    machine.tapeAlphabet().setBlank(line);

    // Final states
    line = Utils::nextLine(file_stream);
    machine.setFinalStates(Utils::split(line, ' '));

    // Read transitions
    line = Utils::nextLine(file_stream);

    while (!line.empty()) {
      machine.addTransition(line);
      line = Utils::nextLine(file_stream);
    }

  } catch (const std::exception& e) {
    std::string message = "Error on Line: " + line + "\n";
    message += std::string("||") + e.what() + "\n";

    throw std::runtime_error(message);
  }

  return machine;
}

}  // namespace turing
