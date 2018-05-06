#include "triangle_verifier.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>

// Statement coverage
TEST(TriangleVerifier, C0) {
  // cover 1st if
  ASSERT_EQ("Invalid input", triangle::triangle_verifier(0, 0, 0));

  // cover 2nd if
  ASSERT_EQ("Not a triangle", triangle::triangle_verifier(1, 2, 3));

  // cover 3rd if
  ASSERT_EQ("Equilateral", triangle::triangle_verifier(5, 5, 5));

  // cover  3rd else if and else
  ASSERT_EQ("Isosceles", triangle::triangle_verifier(2, 2, 3));
  ASSERT_EQ("Scalene", triangle::triangle_verifier(3, 4, 5));
}

// DD-path coverage
TEST(TriangleVerifier, C1) {
  // 1st if is true, and return
  ASSERT_EQ("Invalid input", triangle::triangle_verifier(0, 0, 0));

  // 1st if is false, 2nd if is true, and return
  ASSERT_EQ("Not a triangle", triangle::triangle_verifier(1, 2, 3));

  // 1st and 2nd if are false, and 3rd if is true, and return
  ASSERT_EQ("Equilateral", triangle::triangle_verifier(5, 5, 5));

  // 1st and 2nd if are false, and 3rd "else part" is true, and return
  ASSERT_EQ("Isosceles", triangle::triangle_verifier(2, 2, 3));

  // 1st and 2nd if are false, and 3rd "else if part" is true, and return
  ASSERT_EQ("Scalene", triangle::triangle_verifier(3, 4, 5));
}