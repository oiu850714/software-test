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
TEST(NextDateVerifier, C1) {

  // 執行 1st "big" if
  ASSERT_EQ(DATE_INVALID, NextDate_verifier(Date(1811, 13, 30)));

  // 2nd if: 大月跟小月，還有二月
  ASSERT_EQ(Date(2000, 01, 16), NextDate_verifier(Date(2000, 01, 15)));
  ASSERT_EQ(Date(2000, 04, 16), NextDate_verifier(Date(2000, 04, 15)));
  ASSERT_EQ(Date(2000, 02, 16), NextDate_verifier(Date(2000, 02, 15)));

  // 3rd if: 閏年跟非閏年
  ASSERT_EQ(Date(2000, 02, 29), NextDate_verifier(Date(2000, 02, 28)));
  ASSERT_EQ(Date(2001, 03, 01), NextDate_verifier(Date(2001, 02, 28)));

  // 4th if:
  // 非月底
  ASSERT_EQ(Date(2000, 06, 16), NextDate_verifier(Date(2000, 06, 15)));

  // 月底，非 12 月跟 12 月
  ASSERT_EQ(Date(2000, 07, 01), NextDate_verifier(Date(2000, 06, 30)));
  ASSERT_EQ(Date(2001, 01, 01), NextDate_verifier(Date(2000, 12, 31)));
}

// No loop, same as C1
TEST(NextDateVerifier, C2) {

  // 執行 1st "big" if
  ASSERT_EQ(DATE_INVALID, NextDate_verifier(Date(1811, 13, 30)));

  // 2nd if: 大月跟小月，還有二月
  ASSERT_EQ(Date(2000, 01, 16), NextDate_verifier(Date(2000, 01, 15)));
  ASSERT_EQ(Date(2000, 04, 16), NextDate_verifier(Date(2000, 04, 15)));
  ASSERT_EQ(Date(2000, 02, 16), NextDate_verifier(Date(2000, 02, 15)));

  // 3rd if: 閏年跟非閏年
  ASSERT_EQ(Date(2000, 02, 29), NextDate_verifier(Date(2000, 02, 28)));
  ASSERT_EQ(Date(2001, 03, 01), NextDate_verifier(Date(2001, 02, 28)));

  // 4th if:
  // 非月底
  ASSERT_EQ(Date(2000, 06, 16), NextDate_verifier(Date(2000, 06, 15)));

  // 月底，非 12 月跟 12 月
  ASSERT_EQ(Date(2000, 07, 01), NextDate_verifier(Date(2000, 06, 30)));
  ASSERT_EQ(Date(2001, 01, 01), NextDate_verifier(Date(2000, 12, 31)));
}

} // namespace