#include "triangle_verifier.h"
#include <string>

#define DOMAIN_LOW 1
#define DOMAIN_UP 200

std::string triangle::triangle_verifier(int a, int b, int c) {
  if ((a < DOMAIN_LOW || a > DOMAIN_UP) || (b < DOMAIN_LOW || b > DOMAIN_UP) ||
      (c < DOMAIN_LOW || c > DOMAIN_UP)) {
    return "Invalid input";
  }

  if (!(a < b + c && b < c + a && c < a + b)) {
    return "Not a triangle";
  }

  if (a == b && b == c) {
    return "Equilateral";
  } else if (a != b && b != c && c != a) {
    return "Scalene";
  } else
    return "Isosceles";
}
// namespace triangle