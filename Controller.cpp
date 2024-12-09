#include "Controller.h"

#include <iostream>
#include <random>

#include "AuxiliaryFunctions.h"
#include "Key.h"
#include "Model.h"

namespace {
const unsigned int kMaxLengthNum = 2;
const unsigned int kMinLengthNum = 1;
}  // namespace

namespace Controller {
void GenerateKey() {
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

  Model::GenerateKey(keys, p, q);

  std::cout << "\nОткрытый ключ: {" << keys[0].value << ", " << keys[0].product
            << "}\n";
  std::cout << "Закрытый ключ: {" << keys[1].value << ", " << keys[1].product
            << "}\n\n";
}

void Encrypt() {
  int message = 0;
  Key key;

  std::cout << "Введите сообщение: ";
  std::cin >> message;

  if (message < 0) {
    std::cout << "\nВведено некорректное значение\n\n";
    return;
  }

  std::cout << "Введите ключ: ";
  std::cin >> key.value >> key.product;

  if (key.value < 0 || key.product < 0) {
    std::cout << "\nВведены некорректные значения\n\n";
    return;
  }

  message = Model::Encrypt(message, key);

  std::cout << "\nЗначение: " << message << "\n\n";
}

void Descrypt() {
  int message = 0;
  Key key;

  std::cout << "Введите сообщение: ";
  std::cin >> message;

  if (message < 0) {
    std::cout << "\nВведено некорректное значение\n\n";
    return;
  }

  std::cout << "Введите ключ: ";
  std::cin >> key.value >> key.product;

  if (key.value < 0 || key.product < 0) {
    std::cout << "\nВведены некорректные значения\n\n";
    return;
  }

  message = Model::Descrypt(message, key);

  std::cout << "\nЗначение: " << message << "\n\n";
}
}  // namespace Controller
