#include "gtest/gtest.h"
#include "state/state.hpp"
#include "state/transition.hpp"
#include "utils/utils.hpp"

namespace turing {

class TransitionTest : public ::testing::Test {
protected:
  void SetUp() override {
    s1_ = new State("s1");
    s2_ = new State("s2");

    transition_ = Transition({"0"}, s2_, {"1"}, {Move::Left});

    s1_->addTransition(transition_);
  }

  void TearDown() override {
    delete s1_;
    delete s2_;
  }

  Transition transition_;

  State* s1_;
  State* s2_;
};

TEST_F(TransitionTest, InputSymbols) {
  ASSERT_EQ(transition_.inputSymbols()[0], "0");
}

TEST_F(TransitionTest, OutputSymbols) {
  ASSERT_EQ(transition_.outputSymbols()[0], "1");
}

TEST_F(TransitionTest, Moves) {
  ASSERT_EQ(transition_.moves()[0], Move::Left);
}

TEST_F(TransitionTest, NextStateName) {
  ASSERT_EQ(transition_.nextStateName(), "s2");
}

TEST_F(TransitionTest, NextState) {
  std::vector<Tape> tapes;
  Alphabet tape_alphabet;
  tape_alphabet.setSymbols({"0", "1"});

  tapes.push_back(Tape(tape_alphabet));
  tapes[0].setInputString("01", tape_alphabet);

  auto transition = s1_->transitions({"0"});
  auto next_state = transition.begin()->nextState(tapes);

  ASSERT_EQ(next_state->name(), "s2");
}


}  // namespace turing
