#include "NextDate_verifier.h"
#include "gtest/gtest.h"

#include <string>
namespace {

// normal boundary value test for NextDate problem
// input domain: 1812/01/01 - 2012/12/31
TEST(NextDateVerifierBoundaryValueTest, WeakNormal) {
  // story 1: just compile this file
  
  // story 2, 3, 4: day, month ,year are embedded in Date parameters

  // story 5: day belows 1
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 7, 0)));

  // story 6: day above 31
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 7, 32)));

  // story 7, 8, 9, 10: month/year below/above
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1811, 7, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2013, 7, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 0, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 13, 15)));

  // story 11: Day = 31 in a 30 day month.
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2000, 6, 31)));

  // story 12: Day = 30 in Frbruary (note: also need Day = 31 in February).
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2000, 2, 30)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2000, 2, 31)));

  // story 13: Day = 29 in Februay in a common year.
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2001, 2, 29)));

  // story 14: Day = 29 in Frbruary in a leap year.
  EXPECT_EQ(Date(2000, 3, 1), NextDate_verifier(Date(2000, 2, 29)));

  // story 15: A year divisible by 4 is a leap year (except for century years).
  EXPECT_EQ(Date(2004, 3, 1), NextDate_verifier(Date(2004, 2, 29)));

  // story 16: A year not divisible by 4 is a common year.
  EXPECT_EQ(Date(2003, 3, 1), NextDate_verifier(Date(2003, 2, 28)));

  // story 17: A century year not divisible by 400 is a common year.
  EXPECT_EQ(Date(1900, 3, 1), NextDate_verifier(Date(1900, 2, 28)));

  // story 18: A century year divisible by 400 is a leap year.
  EXPECT_EQ(Date(2000, 2, 29), NextDate_verifier(Date(2000, 2, 28)));

  // story 19: Increment a non-last day of a month.
  EXPECT_EQ(Date(1812, 7, 16), NextDate_verifier(Date(1812, 7, 15)));

  // story 20: Increment the last day of a 30-day month.
  EXPECT_EQ(Date(1912, 7, 1), NextDate_verifier(Date(1912, 6, 30)));

  // story 21: Increment the last day of a 31-day month.
  EXPECT_EQ(Date(1912, 8, 1), NextDate_verifier(Date(1912, 7, 31)));

}

} // namespace