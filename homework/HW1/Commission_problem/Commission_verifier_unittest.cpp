#include "Commission_verifier.h"
#include "gtest/gtest.h"

#include <string>
namespace {

// notica that I split output range, instead of input domain

// boundary value test for Commission problem
// "output" domain: 10 - 1420
TEST(CommissionVerifierBoundaryValueTest, TextBook) {
  EXPECT_EQ(Commission(100, 10),
            Commission_verifier(1, 1, 1)); // output minimum
  EXPECT_EQ(Commission(125, 12.5),
            Commission_verifier(1, 1, 2)); // output minimum+
  EXPECT_EQ(Commission(130, 13),
            Commission_verifier(1, 2, 1)); // output minimum+
  EXPECT_EQ(Commission(145, 14.5),
            Commission_verifier(2, 1, 1)); // output minimum+
  EXPECT_EQ(Commission(500, 50), Commission_verifier(5, 5, 5)); // midpoint
  EXPECT_EQ(Commission(975, 97.5),
            Commission_verifier(10, 10, 9)); // border point-
  EXPECT_EQ(Commission(970, 97),
            Commission_verifier(10, 9, 10)); // border point-
  EXPECT_EQ(Commission(955, 95.5),
            Commission_verifier(9, 10, 10)); // border point-
  EXPECT_EQ(Commission(1000, 100),
            Commission_verifier(10, 10, 10)); // border point
  EXPECT_EQ(Commission(1025, 103.75),
            Commission_verifier(10, 10, 11)); // border point+
  EXPECT_EQ(Commission(1030, 104.5),
            Commission_verifier(10, 11, 10)); // border point+
  EXPECT_EQ(Commission(1045, 106.75),
            Commission_verifier(11, 10, 10)); // border point+
  EXPECT_EQ(Commission(1400, 160), Commission_verifier(14, 14, 14)); // midpoint
  EXPECT_EQ(Commission(1775, 216.25),
            Commission_verifier(18, 18, 17)); // border point-
  EXPECT_EQ(Commission(1770, 215.5),
            Commission_verifier(18, 17, 18)); // border point-
  EXPECT_EQ(Commission(1755, 213.25),
            Commission_verifier(17, 18, 18)); // border point-
  EXPECT_EQ(Commission(1800, 220),
            Commission_verifier(18, 18, 18)); // border point
  EXPECT_EQ(Commission(1825, 225),
            Commission_verifier(18, 18, 19)); // border point+
  EXPECT_EQ(Commission(1830, 226),
            Commission_verifier(18, 19, 18)); // border point+
  EXPECT_EQ(Commission(1845, 229),
            Commission_verifier(19, 18, 18)); // border point+
  EXPECT_EQ(Commission(4800, 820), Commission_verifier(48, 48, 48)); // midpoint
  EXPECT_EQ(Commission(7775, 1415),
            Commission_verifier(70, 80, 89)); // output maximum-
  EXPECT_EQ(Commission(7770, 1414),
            Commission_verifier(70, 79, 90)); // output maximum-
  EXPECT_EQ(Commission(7755, 1411),
            Commission_verifier(69, 80, 90)); // output maximum-
  EXPECT_EQ(Commission(7800, 1420),
            Commission_verifier(70, 80, 90)); // output maximum
}

// robust boundary value test for Commission problem
// "output" domain: 10 - 1420
TEST(CommissionVerifierBoundaryValueTest, Robust) {
  EXPECT_EQ(INVALID_COMMISSION, Commission_verifier(0, 1, 1)); // output minimum
  EXPECT_EQ(INVALID_COMMISSION,
            Commission_verifier(1, 0, 1)); // output minimum+
  EXPECT_EQ(INVALID_COMMISSION,
            Commission_verifier(1, 1, 0)); // output minimum+

  EXPECT_EQ(INVALID_COMMISSION,
            Commission_verifier(71, 80, 90)); // output minimum
  EXPECT_EQ(INVALID_COMMISSION,
            Commission_verifier(70, 81, 90)); // output minimum+
  EXPECT_EQ(INVALID_COMMISSION,
            Commission_verifier(70, 80, 91)); // output minimum+
}

// random input test for boundary value test for triangle problem
// "output" domain: 10 - 1420
TEST(CommissionVerifierBoundaryValueTest, Random) {
  EXPECT_EQ(Commission(4900, 840), Commission_verifier(50, 30, 70));
  EXPECT_EQ(Commission(2000, 260), Commission_verifier(20, 20, 20));
}

// Equivalence class test for Commission problem
//
// M1 = { month: month has 30 days}
// M2 = { month: month has 31 days}
// M3 = { month: month is February}
// D1 = {day: 1 ≤ day ≤ 28}, D2 = {day: day = 29}
// D3 = {day: day = 30}, D4 = {day: day = 31}
// Y1 = {year: year = 2000 }
// Y2 = {year: year is a non-century leap year},
// Y3 = {year: year is a common year}

TEST(CommissionVerifierEquivalenceClassTest, StrongNormal) {
  // just copy test cases from page 111 on textbook
  EXPECT_EQ(Commission(500, 50), Commission_verifier(5, 5, 5));
  EXPECT_EQ(Commission(1500, 175), Commission_verifier(15, 15, 15));
  EXPECT_EQ(Commission(2500, 360), Commission_verifier(25, 25, 25));
}

// decision table method
// according to chapter 07 p.32, same as equivalence class test
TEST(CommissionVerifierDecisionTableTest, ALL) {
  EXPECT_EQ(Commission(500, 50), Commission_verifier(5, 5, 5));
  EXPECT_EQ(Commission(1500, 175), Commission_verifier(15, 15, 15));
  EXPECT_EQ(Commission(2500, 360), Commission_verifier(25, 25, 25));
}

} // namespace
