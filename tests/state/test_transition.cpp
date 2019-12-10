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

    tape_.alphabet().addSymbols("0 1");
    tape_.setInputString("01");

    transition_ = Transition({"0"}, {"1"}, s2_, Move::Left);
  }

  void TearDown() override {
    delete s1_;
    delete s2_;
  }

  Transition transition_;
  Tape<1> tape_;

  State* s1_;
  State* s2_;
};

// TEST_F(TransitionTest, InputSymbol) { ASSERT_EQ(transition_.inputSymbol(), "0"); }
//
// TEST_F(TransitionTest, StackSymbol) { ASSERT_EQ(transition_.stackSymbol(), "A"); }
//
// TEST_F(TransitionTest, NextStateName) { ASSERT_EQ(transition_.nextStateName(), "s2");
// }
//
// TEST_F(TransitionTest, newStackSymbols) {
//   ASSERT_EQ(transition_.newStackSymbols(), "AB");
// }
//
// TEST_F(TransitionTest, NextState) {
//   ASSERT_EQ(tape_.peek(), transition_.inputSymbol());
//   ASSERT_EQ(stack_.top(), transition_.stackSymbol());
//
//   auto* new_state = transition_.nextState(tape_, stack_);
//
//   ASSERT_EQ(new_state->name(), "s2");
//
//   ASSERT_EQ(tape_.peek(), "1");
//
//   ASSERT_EQ(stack_.top(), "A");
//   ASSERT_EQ(stack_.size(), 2);
// }
//
// TEST_F(TransitionTest, nextStateEmptyStack) {
//   stack_.clear();
//   ASSERT_TRUE(stack_.empty());
//
//   ASSERT_THROW({ transition_.nextState(tape_, stack_); }, std::runtime_error);
// }
//
// TEST_F(TransitionTest, InvalidInputSymbol) {
//   tape_.setInputString("1");
//   ASSERT_EQ(tape_.size(), 1);
//
//   // Tape has symbol "1", but transition needs symbol "0"
//   ASSERT_EQ(tape_.peek(), "1");
//   ASSERT_EQ(transition_.inputSymbol(), "0");
//
//   ASSERT_EQ(transition_.nextState(tape_, stack_), nullptr);
// }
//
// TEST_F(TransitionTest, InvalidStackSymbol) {
//   stack_.setStartSymbol("B");
//
//   // Stack has symbol "B", but transition needs symbol "A"
//   ASSERT_EQ(stack_.top(), "B");
//   ASSERT_EQ(transition_.stackSymbol(), "A");
//
//   ASSERT_EQ(transition_.nextState(tape_, stack_), nullptr);
// }
//
// TEST_F(TransitionTest, NoPush) {
//   ASSERT_EQ(tape_.peek(), "0");
//   ASSERT_EQ(stack_.top(), "A");
//   ASSERT_EQ(stack_.size(), 1);
//
//   transition_ = Transition("0", "A", s2_, Utils::lambda);
//   transition_.nextState(tape_, stack_);
//
//   ASSERT_EQ(stack_.size(), 0);
// }
//
// TEST_F(TransitionTest, Lambda) {
//   ASSERT_EQ(tape_.peek(), "0");
//   ASSERT_EQ(stack_.top(), "A");
//
//   // Lamda transition
//   transition_ = Transition(Utils::lambda, "A", s2_, "AB");
//   transition_.nextState(tape_, stack_);
//
//   ASSERT_EQ(tape_.peek(), "0");
// }

}  // namespace turing
