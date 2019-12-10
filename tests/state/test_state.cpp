#include "gtest/gtest.h"
#include "state/state.hpp"
#include "state/transition.hpp"

namespace turing {

class StateTest : public ::testing::Test {
protected:
  void SetUp() override {
    s1_ = new State("s1");
    s2_ = new State("s2");
  }

  void TearDown() override {
    delete s1_;
    delete s2_;
  }

  State* s1_;
  State* s2_;
};

TEST_F(StateTest, Name) { ASSERT_EQ(s1_->name(), "s1"); }

TEST_F(StateTest, EmptyNameInit) {
  ASSERT_THROW({ State s(""); }, std::runtime_error);
}

TEST_F(StateTest, isFinal) {
  ASSERT_FALSE(s1_->isFinal());

  s1_->setFinal(true);

  ASSERT_TRUE(s1_->isFinal());
}

TEST_F(StateTest, getTransitions) {
  auto transitions = s1_->transitions({"a"});

  ASSERT_TRUE(transitions.empty());
}

TEST_F(StateTest, addTransition) {
  s1_->addTransition(Transition({"a"}, {"c"}, s2_, Move::Left));
  s1_->addTransition(Transition({"a"}, {"c"}, s1_, Move::Right));

  auto transitions = s1_->transitions({"a"});
  ASSERT_EQ(transitions.size(), 2);
}

TEST_F(StateTest, addDuplicatedTransition) {
  s1_->addTransition(Transition({"a"}, {"c"}, s2_, Move::Left));
  s1_->addTransition(Transition({"a"}, {"c"}, s2_, Move::Left));

  auto transitions = s1_->transitions({"a"});

  // The transition won't be repeated twice
  ASSERT_EQ(transitions.size(), 1);
}

}  // namespace turing
