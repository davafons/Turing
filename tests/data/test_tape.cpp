#include "gtest/gtest.h"

#include "data/tape.hpp"

namespace turing {

class SimpleTapeTest : public ::testing::Test {
protected:
  void SetUp() override {
    tape_.alphabet().addSymbols("A B C");
    tape_.setInputString("A B Z");
  }

  Tape<1> tape_;
};

TEST_F(SimpleTapeTest, InputStringConstructor) {
  tape_ = Tape<1>("a b c");

  ASSERT_EQ(tape_.alphabet().size(), 3);
  ASSERT_EQ(tape_.size(), 3);
}

TEST_F(SimpleTapeTest, AlphabetConstructor) {
  tape_ = Tape<1>("a b c", "a b");

  ASSERT_EQ(tape_.alphabet().size(), 2);
  ASSERT_EQ(tape_.size(), 2);
}

TEST_F(SimpleTapeTest, Size) { ASSERT_EQ(tape_.size(), 2); }

TEST_F(SimpleTapeTest, Peek) { ASSERT_EQ(tape_.peek(), "A"); }

TEST_F(SimpleTapeTest, Move) {
  ASSERT_EQ(tape_.peek(), "A");

  tape_.moveRight();
  ASSERT_EQ(tape_.peek(), "B");

  tape_.moveRight();
  ASSERT_EQ(tape_.peek(), tape_.alphabet().blank());

  tape_.moveLeft();
  ASSERT_EQ(tape_.peek(), "B");

  tape_.moveLeft();
  ASSERT_EQ(tape_.peek(), "A");

  tape_.moveLeft();
  ASSERT_EQ(tape_.peek(), tape_.alphabet().blank());
}

} // namespace turing
