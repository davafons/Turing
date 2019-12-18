#include "tape.hpp"

#include <iomanip>

#include "utils/utils.hpp"

namespace turing {

/*!
 *  \class Tape
 *  \brief Tape used by the Turing Machine to read/write.
 *
 *  All symbols on the Tape must be recognized by the alphabet.
 *  The Tape head can move to Left/Right/Stop.
 */

/*!
 *  Construct a Tape object with the given alphabet.
 */
Tape::Tape(const Alphabet& alphabet) : alphabet_(alphabet) {}

/*!
 *  Return the Alphabet associated with this Tape.
 */
const Alphabet& Tape::alphabet() const {
  return alphabet_.get();
}

/*
 *  Return if the Tape is empty.
 */
bool Tape::empty() const {
  return data_.empty();
}

/*!
 *  Get the current symbol pointed by the tape head.
 */
Symbol Tape::peek() const {
  return at(tape_head_);
}

/*!
 *  Write a new symbol on the tape head position.
 *
 *  !WARNING: This methods throws in case that the symbol being written is not on the
 *  alphabet.
 */
void Tape::write(Symbol symbol) {
  if (!alphabet_.get().contains(symbol) && symbol != alphabet_.get().blank()) {
    throw std::runtime_error("Can't write Symbol " + symbol + ". Not in Alphabet.");
  }

  data_[tape_head_] = symbol;
}

/*!
 *  Move the tape head in the given direction.
 */
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

/*!
 *  Clear all data from the Tape and reset the head to 0.
 */
void Tape::reset() {
  tape_head_ = 0;
  data_.clear();
}

/*!
 *  Split the input string using the input alphabet and write it on the tape.
 *
 *  !WARNING: input symbols that aren't on the alphabet will be ignored.
 *  If a symbol can't be written on the Tape, an exception will be thrown.
 *
 */
void Tape::setInputString(const std::string& input_line,
                          const Alphabet& input_alphabet) {
  reset();

  auto symbols = input_alphabet.splitInSymbols(input_line);

  for (int i = 0; i < symbols.size(); ++i) {
    write(symbols[i]);
    move(Move::Right);
  }

  tape_head_ = 0;
}

/*!
 *  Return the element at the position "idx".
 *  Because we're using a map to simulate an "infinite" tape, return blank if the index
 *  isn't contained on the map, or the element otherwise.
 */
Symbol Tape::at(int idx) const {
  if (!data_.count(idx)) {
    return alphabet_.get().blank();
  }

  return data_.at(idx);
}

/*!
 *  Print the Tape.
 */
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

/*!
 *  Output operator for easily writing a vector of tapes
 */
std::ostream& operator<<(std::ostream& os, const std::vector<Tape>& tapes) {
  for (int i = 0; i < tapes.size(); ++i) {
    os << "Tape " << i << std::endl;
    os << tapes[i] << std::endl;
  }

  return os;
}

}  // namespace turing
