#include "NextDate_verifier.h"
#include "gtest/gtest.h"

#include <string>
namespace {

// normal boundary value test for NextDate problem
// input domain: 1812/01/01 - 2012/12/31
TEST(NextDateVerifierBoundaryValueTest, WeakNormal) {
  EXPECT_EQ(Date(1812, 7, 16), NextDate_verifier(Date(1812, 7, 15)));
  EXPECT_EQ(Date(1813, 7, 16), NextDate_verifier(Date(1813, 7, 15)));
  EXPECT_EQ(Date(1912, 7, 16), NextDate_verifier(Date(1912, 7, 15)));
  EXPECT_EQ(Date(2011, 7, 16), NextDate_verifier(Date(2011, 7, 15)));
  EXPECT_EQ(Date(2012, 7, 16), NextDate_verifier(Date(2012, 7, 15)));
  EXPECT_EQ(Date(1912, 1, 16), NextDate_verifier(Date(1912, 1, 15)));
  EXPECT_EQ(Date(1912, 2, 16), NextDate_verifier(Date(1912, 2, 15)));
  EXPECT_EQ(Date(1912, 7, 16), NextDate_verifier(Date(1912, 7, 15)));
  EXPECT_EQ(Date(1912, 11, 16), NextDate_verifier(Date(1912, 11, 15)));
  EXPECT_EQ(Date(1912, 12, 16), NextDate_verifier(Date(1912, 12, 15)));
  EXPECT_EQ(Date(1912, 7, 2), NextDate_verifier(Date(1912, 7, 1)));
  EXPECT_EQ(Date(1912, 7, 3), NextDate_verifier(Date(1912, 7, 2)));
  EXPECT_EQ(Date(1912, 7, 16), NextDate_verifier(Date(1912, 7, 15)));
  EXPECT_EQ(Date(1912, 7, 31), NextDate_verifier(Date(1912, 7, 30)));
  EXPECT_EQ(Date(1912, 8, 1), NextDate_verifier(Date(1912, 7, 31)));
}

// invalid(robust) input test for boundary value test for NextDate problem
// input domain: 1812/01/01 - 2012/12/31
TEST(NextDateVerifierBoundaryValueTest, WeakRobust) {
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1811, 7, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2013, 7, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 0, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 13, 15)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 7, 0)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1912, 7, 32)));
}

// no strong normal and strong robust test cases for boundary value tesr for
// NextDate problem because it is too tedious

// random input test for boundary value test for triangle problem
// input domain: 1812/01/01 - 2012/12/31
TEST(NextDateVerifierBoundaryValueTest, Random) {
  EXPECT_EQ(Date(1950, 7, 1), NextDate_verifier(Date(1950, 6, 30)));
  EXPECT_EQ(Date(2000, 2, 29), NextDate_verifier(Date(2000, 2, 28)));
}

// Equivalence class test for NextDate problem
//
// M1 = { month: month has 30 days}
// M2 = { month: month has 31 days}
// M3 = { month: month is February}
// D1 = {day: 1 ≤ day ≤ 28}, D2 = {day: day = 29}
// D3 = {day: day = 30}, D4 = {day: day = 31}
// Y1 = {year: year = 2000 }
// Y2 = {year: year is a non-century leap year},
// Y3 = {year: year is a common year}

TEST(NextDateVerifierEquivalenceClassTest, StrongNormal) {

  // just copy test cases from page 111 on textbook
  EXPECT_EQ(Date(2000, 6, 15), NextDate_verifier(Date(2000, 6, 14)));
  EXPECT_EQ(Date(1996, 6, 15), NextDate_verifier(Date(1996, 6, 14)));
  EXPECT_EQ(Date(2002, 6, 15), NextDate_verifier(Date(2002, 6, 14)));
  EXPECT_EQ(Date(2000, 6, 30), NextDate_verifier(Date(2000, 6, 29)));
  EXPECT_EQ(Date(1996, 6, 30), NextDate_verifier(Date(1996, 6, 29)));
  EXPECT_EQ(Date(2002, 6, 30), NextDate_verifier(Date(2002, 6, 29)));
  EXPECT_EQ(Date(2000, 7, 1), NextDate_verifier(Date(2000, 6, 30)));
  EXPECT_EQ(Date(1996, 7, 1), NextDate_verifier(Date(1996, 6, 30)));
  EXPECT_EQ(Date(2002, 7, 1), NextDate_verifier(Date(2002, 6, 30)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2000, 6, 31)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1996, 6, 31)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2002, 6, 31)));
  EXPECT_EQ(Date(2000, 7, 15), NextDate_verifier(Date(2000, 7, 14)));
  EXPECT_EQ(Date(1996, 7, 15), NextDate_verifier(Date(1996, 7, 14)));
  EXPECT_EQ(Date(2002, 7, 15), NextDate_verifier(Date(2002, 7, 14)));
  EXPECT_EQ(Date(2000, 7, 30), NextDate_verifier(Date(2000, 7, 29)));
  EXPECT_EQ(Date(1996, 7, 30), NextDate_verifier(Date(1996, 7, 29)));
  EXPECT_EQ(Date(2002, 7, 30), NextDate_verifier(Date(2002, 7, 29)));
  EXPECT_EQ(Date(2000, 7, 31), NextDate_verifier(Date(2000, 7, 30)));
  EXPECT_EQ(Date(1996, 7, 31), NextDate_verifier(Date(1996, 7, 30)));
  EXPECT_EQ(Date(2002, 7, 31), NextDate_verifier(Date(2002, 7, 30)));
  EXPECT_EQ(Date(2000, 8, 1), NextDate_verifier(Date(2000, 7, 31)));
  EXPECT_EQ(Date(1996, 8, 1), NextDate_verifier(Date(1996, 7, 31)));
  EXPECT_EQ(Date(2002, 8, 1), NextDate_verifier(Date(2002, 7, 31)));
  EXPECT_EQ(Date(2000, 2, 15), NextDate_verifier(Date(2000, 2, 14)));
  EXPECT_EQ(Date(1996, 2, 15), NextDate_verifier(Date(1996, 2, 14)));
  EXPECT_EQ(Date(2002, 2, 15), NextDate_verifier(Date(2002, 2, 14)));
  EXPECT_EQ(Date(2000, 3, 1), NextDate_verifier(Date(2000, 2, 29)));
  EXPECT_EQ(Date(1996, 3, 1), NextDate_verifier(Date(1996, 2, 29)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2002, 2, 29)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2000, 2, 30)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1996, 2, 30)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2002, 2, 30)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2000, 2, 31)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(1996, 2, 31)));
  EXPECT_EQ(DATE_INVALID, NextDate_verifier(Date(2002, 2, 31)));
}
/*
// decision table method
// refer to the ppt of chpater 07, page 7 and 22
TEST(NextDateVerifierDecisionTableTest, ALL) {
  EXPECT_EQ("Not a triangle", NextDate_verifier(4, 1, 2));
  EXPECT_EQ("Not a triangle", NextDate_verifier(1, 4, 2));
  EXPECT_EQ("Not a triangle", NextDate_verifier(1, 2, 4));
  EXPECT_EQ("Equilateral", NextDate_verifier(5, 5, 5));

  // EXPECT_EQ("Invalid input", NextDate_verifier(, , ));
  // impossible

  // EXPECT_EQ("Invalid input", NextDate_verifier(, , ));
  // impossible

  EXPECT_EQ("Isosceles", NextDate_verifier(2, 2, 3));

  // EXPECT_EQ("Invalid input", NextDate_verifier(, , ));
  // impossible

  EXPECT_EQ("Isosceles", NextDate_verifier(2, 3, 2));
  EXPECT_EQ("Isosceles", NextDate_verifier(3, 2, 2));
  EXPECT_EQ("Scalene", NextDate_verifier(3, 4, 5));
}
*/
} // namespace
