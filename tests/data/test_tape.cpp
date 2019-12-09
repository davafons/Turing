#include "gtest/gtest.h"

namespace turing {

class TapeTest : public ::testing::Test {
protected:
  void SetUp() override {}
};

TEST_F(TapeTest, Default) { ASSERT_TRUE(true); }

} // namespace turing
