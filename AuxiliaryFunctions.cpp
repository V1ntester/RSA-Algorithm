#include <cmath>
#include "AuxiliaryFunctions.h"

bool IsPrime(int num) {
  for (size_t i = 2; i < static_cast<size_t>(std::sqrt(num)) + 1; i++) {
    if (num % i == 0) {
      return false;
    }
  }

  return true;
}

bool IsCoprime(int max, int min) {
  int quotient = max % min;

  while (quotient != 0) {
    max = min;
    min = quotient;
    quotient = max % min;
  }

  return min == 1;
}
