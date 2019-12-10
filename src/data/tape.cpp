#include "tape.hpp"

#include "utils/utils.hpp"

namespace turing {

Tape::Tape(const Alphabet& alphabet, int num_tracks)
    : num_tracks_(num_tracks), alphabet_(alphabet) {}

const Alphabet& Tape::alphabet() const {
  return alphabet_;
}

int Tape::numTracks() const {
  return num_tracks_;
}

Cell Tape::peek() const {
  return at(tape_head_);
}

void Tape::write(Cell cell) {
  if (cell.size() != num_tracks_) {
    throw std::runtime_error("Trying to add a Cell of height " +
                             std::to_string(cell.size()) + " to a Tape of height " +
                             std::to_string(num_tracks_));
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

void Tape::setInputString(const std::string& input_string) {
  std::vector<std::string> lines = Utils::split(input_string, '\n');

  int track_num = 0;
  for (const auto& line : lines) {
    int cell_idx = 0;
    for (const auto symbol : alphabet_.splitInSymbols(line)) {
      if (!data_.count(cell_idx)) {
        data_[cell_idx] = Cell(num_tracks_, alphabet_.blank());
      }

      data_[cell_idx][track_num] = symbol;

      ++cell_idx;
    }

    ++track_num;
  }
}

Cell Tape::at(int idx) const {
  if (!data_.count(idx)) {
    return Cell(num_tracks_, alphabet_.blank());
  }

  return data_.at(idx);
}

std::ostream& operator<<(std::ostream& os, const Tape& tape) {

  int first_cell_idx = tape.data_.cbegin()->first;
  int last_cell_idx = tape.data_.crbegin()->first;

  // Write indices
  os << "  ";
  for (int i = first_cell_idx; i <= last_cell_idx; ++i) {
    os << i << "   ";
  }
  os << "\n";

  // Write tape tracks
  for (int track = 0; track < tape.num_tracks_; ++track) {
    os << "[ ";
    for (int cell_idx = first_cell_idx; cell_idx <= last_cell_idx; ++cell_idx) {
      os << tape.at(cell_idx)[track] << " | ";
    }

    os << "\b\b]\n";
  }

  return os;
}

}  // namespace turing
