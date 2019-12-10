#include "tape.hpp"

namespace turing {

Tape::Tape(int rows) : rows_(rows) {}

Alphabet& Tape::alphabet() { return alphabet_; }

const Alphabet& Tape::alphabet() const { return alphabet_; }

int Tape::rows() const { return rows_; }

Cell Tape::peek() const {
  if (!data_.count(tape_head_)) {
    return Cell(rows_, alphabet_.blank());
  }

  return data_.at(tape_head_);
}

void Tape::write(Cell cell) {
  if (cell.size() != rows_) {
    throw std::runtime_error("Trying to add a Cell of height " +
                             std::to_string(cell.size()) + " to a Tape of height " +
                             std::to_string(rows_));
  }

  for (const auto& s : cell) {
    if (!alphabet_.contains(s) && s != alphabet_.blank()) {
      throw std::runtime_error("Can't write Symbol " + s +
                               ". Not in Alphabet.");  // TODO: Print alphabet
    }
  }

  data_[tape_head_] = cell;
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

void Tape::setInputString(const std::vector<Cell>& input) {
  reset();

  for (const auto& cell : input) {
    write(cell);
    ++tape_head_;
  }

  // Reset tape_head to initial position
  tape_head_ = 0;
}

}  // namespace turing
