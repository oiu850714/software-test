#include "triangle_verifier.h"
#include "gtest/gtest.h"

#include <string>
namespace {

// normal boundary value test for triangle problem
// input domain: [1, 200]
TEST(TraingleVerifierTest, NormalBoundaryValue) {
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

// extra test for boundary value test for triangle problem
// input domain: [1, 200]
TEST(TraingleVerifierTest, RobustBoundaryValue) {
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(0, 100, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(201, 100, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 0, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 201, 100));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 100, 0));
  EXPECT_EQ("Invalid input", triangle::triangle_verifier(100, 100, 20));
}
} // namespace