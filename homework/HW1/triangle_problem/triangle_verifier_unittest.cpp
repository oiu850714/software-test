#include "triangle_verifier.h"
#include "gtest/gtest.h"

#include <string>
namespace {

// normal boundary value test for triangle problem
// input domain: [1, 200]
TEST(TraingleVerifierBoundaryValueTest, WeakNormal) {
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(1, 100, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(2, 100, 100));
  EXPECT_EQ("Equilateral", triangle::triangle_verifier(100, 100, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(199, 100, 100));
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(200, 100, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(100, 1, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(100, 2, 100));
  // EXPECT_EQ("Equilateral", triangle::triangle_verifier(100, 100, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(100, 199, 100));
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(100, 200, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(100, 100, 1));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(100, 100, 2));
  // EXPECT_EQ("Equilateral", triangle::triangle_verifier(100, 100, 100));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(100, 100, 199));
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(100, 100, 200));
}

// invalid(robust) input test for boundary value test for triangle problem
// input domain: [1, 200]
TEST(TraingleVerifierBoundaryValueTest, WeakRobust) {
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(0, 100, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(201, 100, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 0, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 201, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 100, 0));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 100, 201));
}

// no strong normal and strong robust test cases for boundary value tesr for
// triangle problem because it is too tedious

// random input test for boundary value test for triangle problem
// input domain: [1, 200]
TEST(TraingleVerifierBoundaryValueTest, Random) {
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(1, 2, 3));
  EXPECT_EQ("Scalene", triangle::triangle_verifier(30, 40, 50));
}

// Equivalence class test for triangle problem
// for classes:
//   Equilateral
//   Isosceles
//   Scalene
//   Not a triangle

// weak normal
TEST(TraingleVerifierEquivalenceClassTest, WeakNormal) {
  EXPECT_EQ("Equilateral", triangle::triangle_verifier(5, 5, 5));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(50, 80, 80));
  EXPECT_EQ("Scalene", triangle::triangle_verifier(3, 4, 5));
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(1, 2, 3));
}

// strong normal
// Because no valid subintervals of either side length exist, the strong normal
// equivalence class test cases are identical to the weak normal equivalence
// test cases.

// weak robust
TEST(TraingleVerifierEquivalenceClassTest, WeakRobust) {
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(-1, 5, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(5, -1, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(5, 5, -1));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(201, 5, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(5, 201, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(5, 5, 201));
}

// strong robust
TEST(TraingleVerifierEquivalenceClassTest, StrongRobust) {
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(-1, 5, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(5, -1, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(5, 5, -1));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(-1, -1, 5));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(-1, 5, -1));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(-1, -1, -1));
}

// decision table method
// refer to the ppt of chpater 07, page 7 and 22
TEST(TraingleVerifierDecisionTableTest, ALL) {
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(4, 1, 2));
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(1, 4, 2));
  EXPECT_EQ("Not a triangle", triangle::triangle_verifier(1, 2, 4));
  EXPECT_EQ("Equilateral", triangle::triangle_verifier(5, 5, 5));

  // EXPECT_EQ("Invalid input", triangle::triangle_verifier(, , ));
  // impossible

  // EXPECT_EQ("Invalid input", triangle::triangle_verifier(, , ));
  // impossible

  EXPECT_EQ("Isosceles", triangle::triangle_verifier(2, 2, 3));

  // EXPECT_EQ("Invalid input", triangle::triangle_verifier(, , ));
  // impossible

  EXPECT_EQ("Isosceles", triangle::triangle_verifier(2, 3, 2));
  EXPECT_EQ("Isosceles", triangle::triangle_verifier(3, 2, 2));
  EXPECT_EQ("Scalene", triangle::triangle_verifier(3, 4, 5));
}

} // namespace