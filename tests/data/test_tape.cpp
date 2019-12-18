#include "data/tape.hpp"
#include "gtest/gtest.h"

namespace turing {

class SimpleTapeTest : public ::testing::Test {
protected:
  void SetUp() override {
    tape_alphabet_.setSymbols({"A", "B", "C"});
    input_alphabet_.setSymbols({"A", "B", "C"});

    tape_ = Tape(tape_alphabet_);

    tape_.setInputString("AB", input_alphabet_);
  }

  Tape tape_;
  Alphabet tape_alphabet_;
  Alphabet input_alphabet_;
};

TEST_F(SimpleTapeTest, Constructor) {
  ASSERT_EQ(tape_.alphabet().size(), 3);
}

TEST_F(SimpleTapeTest, Peek) {
  ASSERT_EQ(tape_.peek(), "A");
}

TEST_F(SimpleTapeTest, Move) {
  ASSERT_EQ(tape_.peek(), "A");

  tape_.move(Move::Right);
  ASSERT_EQ(tape_.peek(), "B");

  tape_.move(Move::Right);
  ASSERT_EQ(tape_.peek(), tape_.alphabet().blank());

  tape_.move(Move::Left);
  ASSERT_EQ(tape_.peek(), "B");

  tape_.move(Move::Left);
  ASSERT_EQ(tape_.peek(), "A");

  tape_.move(Move::Left);
  ASSERT_EQ(tape_.peek(), tape_.alphabet().blank());
}

TEST_F(SimpleTapeTest, Reset) {
  tape_.reset();
}

TEST_F(SimpleTapeTest, SetInputString) {
  tape_alphabet_.setSymbols({"X", "Y", "Z"});
  input_alphabet_.setSymbols({"X", "Y", "Z"});

  tape_.setInputString("XYZ", input_alphabet_);

  ASSERT_EQ(tape_.peek(), "X");
}

TEST_F(SimpleTapeTest, WriteCorrectSymbol) {
  ASSERT_EQ(tape_.peek(), "A");

  tape_.write("C");

  ASSERT_EQ(tape_.peek(), "C");
}

TEST_F(SimpleTapeTest, WriteIncorrectSymbol) {
  ASSERT_EQ(tape_.peek(), "A");

  ASSERT_THROW({ tape_.write("%"); }, std::runtime_error);
}

}  // namespace turing
