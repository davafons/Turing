#include "data/alphabet.hpp"
#include "gtest/gtest.h"

namespace turing {

class AlphabetTest : public ::testing::Test {
protected:
  void SetUp() override { alphabet_.setSymbols({"a", "b", "c"}); }

  Alphabet alphabet_;
};

TEST_F(AlphabetTest, Empty) {
  ASSERT_FALSE(alphabet_.empty());
}

TEST_F(AlphabetTest, Reset) {
  alphabet_.reset();

  ASSERT_TRUE(alphabet_.empty());
}

TEST_F(AlphabetTest, Contains) {
  ASSERT_TRUE(alphabet_.contains("a"));
  ASSERT_TRUE(alphabet_.contains("b"));
}

TEST_F(AlphabetTest, NotContains) {
  ASSERT_FALSE(alphabet_.contains("1"));
  ASSERT_FALSE(alphabet_.contains("%"));
}

TEST_F(AlphabetTest, SplitInSymbols) {
  // Alphabet has "a b c" symbols
  auto symbols = alphabet_.splitInSymbols("abc");

  ASSERT_EQ(symbols.size(), 3);
  ASSERT_EQ(symbols[0], "a");
  ASSERT_EQ(symbols[1], "b");
  ASSERT_EQ(symbols[2], "c");
}

TEST_F(AlphabetTest, UnrecognizedSymbols) {
  // Alphabet has "a b c" symbols
  auto symbols = alphabet_.splitInSymbols("a0b1");

  // Only "a" and "b" will be splitted. "0" and "1" are ignored.
  ASSERT_EQ(symbols.size(), 2);
  ASSERT_EQ(symbols[0], "a");
  ASSERT_EQ(symbols[1], "b");
}

TEST_F(AlphabetTest, AddSymbol) {
  alphabet_.addSymbol("d");

  ASSERT_EQ(alphabet_.size(), 4);
}

TEST_F(AlphabetTest, SetSymbols) {
  alphabet_.setSymbols({"X", "Y"});

  auto symbols = alphabet_.splitInSymbols("X Y");

  ASSERT_EQ(symbols.size(), 2);
  ASSERT_EQ(symbols[0], "X");
  ASSERT_EQ(symbols[1], "Y");
}

TEST_F(AlphabetTest, SetBlank) {
  alphabet_.setBlank("z");

  ASSERT_EQ(alphabet_.blank(), "z");
}

TEST_F(AlphabetTest, SetExistentBlank) {
  ASSERT_EQ(alphabet_.blank(), ".");

  // Shouldn't change as "a" is already on the Alphabet
  alphabet_.setBlank("a");

  ASSERT_EQ(alphabet_.blank(), ".");
}

}  // namespace turing
