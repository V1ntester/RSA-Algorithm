#include <cmath>
#include <cstddef>
#include <iostream>
#include <random>

using std::size_t;

struct Key {
  int value;
  int product;
};

namespace {
const unsigned int kMaxLengthNum = 2;
const unsigned int kMinLengthNum = 1;
}  // namespace

bool IsPrime(int num) {
  for (size_t i = 2; i < static_cast<int>(std::sqrt(num)) + 1; i++) {
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

void GenerateKeys(Key *keys, int firstNum, int secondNum) {
  int eulerFunctionValue = (firstNum - 1) * (secondNum - 1);
  int e = 0;
  bool isComrime = false;

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

int main() {
  char userInput = ' ';

  while (userInput != 'q') {
    std::cout
        << "Доступные действия:\na — сгенерировать ключ\nb — зашифровать\nc — "
           "расшифровать\nq — выход\n\nВведите команду: ";

    std::cin >> userInput;

    switch (userInput) {
      case 'a': {
        int p = 0;
        int q = 0;

        std::random_device r{};
        std::default_random_engine randomEngine(r());
        std::uniform_int_distribution distribution(
            static_cast<int>(std::pow(10, kMinLengthNum - 1) + 1),
            static_cast<int>(std::pow(10, kMaxLengthNum)));

        while (!IsPrime(p) || p == 0) {
          p = distribution(randomEngine);
        }

        while (!IsPrime(q) || q == 0) {
          q = distribution(randomEngine);
        }

        Key keys[2] = {};

        GenerateKeys(keys, p, q);

        std::cout << "\nОткрытый ключ: {" << keys[0].value << ", "
                  << keys[0].product << "}\n";
        std::cout << "Закрытый ключ: {" << keys[1].value << ", "
                  << keys[1].product << "}\n\n";
        break;
      }
      case 'b': {
        int message = 0;
        Key key;

        std::cout << "Введите сообщение: ";
        std::cin >> message;

        std::cout << "Введите ключ: ";
        std::cin >> key.value >> key.product;

        message = Encrypt(message, key);

        std::cout << "\nЗначение: " << message << "\n\n";
        break;
      }
      case 'c': {
        int message = 0;
        Key key;

        std::cout << "Введите сообщение: ";
        std::cin >> message;

        std::cout << "Введите ключ: ";
        std::cin >> key.value >> key.product;

        message = Descrypt(message, key);

        std::cout << "\nЗначение: " << message << "\n\n";
        break;
      }
      default:
        break;
    }
  }

  return 0;
}
