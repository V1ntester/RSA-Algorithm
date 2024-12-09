#include <cstddef>
#include <iostream>


#include "Controller.h"
#include "Key.h"

using std::size_t;

int main() {
  char userInput = ' ';

  while (userInput != 'q') {
    std::cout
        << "Доступные действия:\na — сгенерировать ключ\nb — зашифровать\nc — "
           "расшифровать\nq — выход\n\nВведите команду: ";

    std::cin >> userInput;

    switch (userInput) {
      case 'a':
        Controller::GenerateKey();
        break;
      case 'b':
        Controller::Encrypt();
        break;
      case 'c':
        Controller::Descrypt();
        break;
      default:
        break;
    }
  }

  return 0;
}
