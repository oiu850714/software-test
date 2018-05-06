#include "Commission_verifier.h"
#include "gtest/gtest.h"

#include <string>
namespace {

TEST(CommissionVerifier, C0) {

  // 執行 1st "big" if 的 statements
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(0, 1, 1));
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(1, 0, 1));
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(1, 1, 0));

  // 執行 2nd if 的 statements
  EXPECT_EQ(Commission(100, 10), Commission_verifier(1, 1, 1));
  EXPECT_EQ(Commission(1025, 103.75), Commission_verifier(10, 10, 11));
  EXPECT_EQ(Commission(1825, 225), Commission_verifier(18, 18, 19));
}

TEST(CommissionVerifier, C1) {

  // 執行 1st "big" if 的 所有 true/false
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(0, 1, 1));
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(1, 0, 1));
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(1, 1, 0));

  // 執行 2nd if 的 statements
  EXPECT_EQ(Commission(100, 10), Commission_verifier(1, 1, 1));
  EXPECT_EQ(Commission(1025, 103.75), Commission_verifier(10, 10, 11));
  EXPECT_EQ(Commission(1825, 225), Commission_verifier(18, 18, 19));
}

TEST(CommissionVerifier, C2) {

  // 執行 1st "big" if 的 所有 true/false
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(0, 1, 1));
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(1, 0, 1));
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(1, 1, 0));

  // 執行 2nd if 的 statements
  EXPECT_EQ(Commission(100, 10), Commission_verifier(1, 1, 1));
  EXPECT_EQ(Commission(1025, 103.75), Commission_verifier(10, 10, 11));
  EXPECT_EQ(Commission(1825, 225), Commission_verifier(18, 18, 19));
}

} // namespace
