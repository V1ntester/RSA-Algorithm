#include "Model.h"

#include <random>

#include "AuxiliaryFunctions.h"
#include "Key.h"

namespace {
int InvertByMod(int value, int mod) {
  int u1 = mod;
  int u2 = 0;
  int v1 = value;
  int v2 = 1;

  while (v1 > 0) {
    int q = u1 / v1;
    int t1 = u1 - q * v1;
    int t2 = u2 - q * v2;
    u1 = v1;
    u2 = v2;
    v1 = t1;
    v2 = t2;
  }

  return (u2 + mod) % mod;
}
}  // namespace

namespace Model {
void GenerateKey(Key *keys, int firstNum, int secondNum) {
  int eulerFunctionValue = (firstNum - 1) * (secondNum - 1);
  int e = 0;

  std::random_device r{};
  std::default_random_engine randomEngine(r());
  std::uniform_int_distribution distribution(1, eulerFunctionValue);

  e = distribution(randomEngine);

  while (!IsCoprime(eulerFunctionValue, e)) {
    e = distribution(randomEngine);
  }

  int d = InvertByMod(e, eulerFunctionValue);
  int product = firstNum * secondNum;

  keys[0] = {e, product};
  keys[1] = {d, product};
}

int Encrypt(int message, Key key) {
  int degree = 0;
  int result = 1;

  while (degree < key.value) {
    result = (result * message) % key.product;
    ++degree;
  }

  return result;
}

int Descrypt(int message, Key key) {
  int degree = 0;
  int result = 1;

  while (degree < key.value) {
    result = (result * message) % key.product;
    ++degree;
  }

  return result;
}
}  // namespace Model
