#include <cstddef>
#include <iostream>

#include "Controller.h"
#include "Key.h"
#include "Navigation.h"

using std::size_t;

namespace {
size_t kNavigationItemsAmount = 3;
}

int main() {
  Navigation::Item navigationItems[] = {
      {.name = "Сгенерировать ключ",
       .key = 'a',
       .functionPtr = Controller::GenerateKey},
      {.name = "Шифровать", .key = 'b', .functionPtr = Controller::Encrypt},
      {.name = "Дешифровать", .key = 'c', .functionPtr = Controller::Descrypt},
  };

  Navigation::Init(navigationItems, kNavigationItemsAmount);

  return 0;
}
