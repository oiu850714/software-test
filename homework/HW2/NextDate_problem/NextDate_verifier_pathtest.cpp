#include "NextDate_verifier.h"
#include "gtest/gtest.h"

namespace {

TEST(NextDateVerifier, C0) {
  // executes 1st "big" if statements
  ASSERT_EQ(DATE_INVALID, NextDate_verifier(Date(1811, 01, 01)));
  ASSERT_EQ(DATE_INVALID, NextDate_verifier(Date(1812, 13, 01)));
  ASSERT_EQ(DATE_INVALID, NextDate_verifier(Date(1812, 01, 32)));

  // executes remaining branches
  ASSERT_EQ(Date(2001, 01, 01), NextDate_verifier(Date(2000, 12, 31)));
}

} // namespace