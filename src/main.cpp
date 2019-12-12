#include <boost/program_options.hpp>
#include <iostream>

#include "core/turing.hpp"
#include "core/turingbuilder.hpp"

namespace po = boost::program_options;

struct Options {
  bool debug_mode{false};
  std::string turing_file{""};
  std::string input{""};
};

void runTuringMachine(turing::Turing& machine, const std::string& input);
bool parseArguments(int argc, char* argv[], Options& options);

int main(int argc, char* argv[]) {
  // Command line arguments
  Options options;

  // Exit if couldn't parse command line arguments
  if (!parseArguments(argc, argv, options)) {
    return 1;
  }

  try {
    // Instantiate Turing Machine from file
    turing::Turing machine = turing::TuringBuilder::fromFile(options.turing_file);
    machine.toggleDebugMode(options.debug_mode);

    runTuringMachine(machine, options.input);

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}

void runTuringMachine(turing::Turing& machine, const std::string& input) {
  std::cout << machine << std::endl << "-----------------" << std::endl;
  std::cout << "Input: " << input << std::endl;
  bool recognized = machine.run(input);
  std::cout << "Recognized: " << std::boolalpha << recognized << std::endl << std::endl;
}

bool parseArguments(int argc, char* argv[], Options& options) {
  po::options_description desc("Options");
  desc.add_options()("help,h", "Show help menu")(
      "FILE",
      po::value<std::string>(&options.turing_file)->required(),
      "Turing machine definition")(

      "debug,D", po::bool_switch(&options.debug_mode), "Show a trace of the execution")(

      "INPUT",
      po::value<std::string>(&options.input)->required(),
      "Input string or file to be recognized by the automata.");

  try {
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);

    if (vm.count("help")) {
      std::cout << "Turing Machine implementation in C++\nSupport for "
                   "Non-Deterministic,Multitape,Multitrack Turing Machines"
                << std::endl;
      std::cout << desc << std::endl;
      return false;
    }

    po::notify(vm);

  } catch (const po::error& e) {
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;
    return false;
  }

  return true;
}
