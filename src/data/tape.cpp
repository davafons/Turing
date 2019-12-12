#include "tape.hpp"

#include <iomanip>

#include "utils/utils.hpp"

namespace turing {

Tape::Tape(const Alphabet& alphabet) : alphabet_(alphabet) {}

const Alphabet& Tape::alphabet() const {
  return alphabet_;
}

bool Tape::empty() const {
  return data_.empty();
}

Symbol Tape::peek() const {
  return at(tape_head_);
}

void Tape::write(Symbol symbol) {
  if (!alphabet_.contains(symbol) && symbol != alphabet_.blank()) {
    throw std::runtime_error("Can't write Symbol " + symbol +
                             ". Not in Alphabet.");  // TODO: Print alphabet
  }

  data_[tape_head_] = symbol;
}

void Tape::move(Move dir) {
  switch (dir) {
    case Move::Left:
      --tape_head_;
      break;

    case Move::Right:
      ++tape_head_;
      break;

    case Move::Stop:
    default:
      break;
  }
}

void Tape::reset() {
  tape_head_ = 0;
  data_.clear();
}

void Tape::setInputString(const std::string& input_line) {
  auto symbols = alphabet_.splitInSymbols(input_line);

  for (int i = 0; i < symbols.size(); ++i) {
    data_[i] = symbols[i];
  }
}

Symbol Tape::at(int idx) const {
  if (!data_.count(idx)) {
    return alphabet_.blank();
  }

  return data_.at(idx);
}

std::ostream& operator<<(std::ostream& os, const Tape& tape) {
  if (tape.empty()) {
    os << "[ (empty) ]";
    return os;
  }

  int first_cell_idx = tape.data_.cbegin()->first - 1;
  int last_cell_idx = tape.data_.crbegin()->first + 1;

  // Write indices
  os << " ";
  for (int i = first_cell_idx; i <= last_cell_idx; ++i) {
    os << i << std::setw(4);
  }
  os << "\n";

  // Write tape tracks
  os << "[ ";
  for (int i = first_cell_idx; i <= last_cell_idx; ++i) {
    os << tape.at(i) << " | ";
  }

  os << "\b\b]\n";

  os << std::setw(3 + (tape.tape_head_ - first_cell_idx) * 4) << "^";

  return os;
}

}  // namespace turing
