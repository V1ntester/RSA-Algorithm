#include "Navigation.h"

#include <cstddef>
#include <iostream>

#include "Controller.h"

namespace {

const size_t kNavigationItemsAmount = 3;

const Navigation::Item kNavigationItems[kNavigationItemsAmount] = {
    {.name = "Сгенерировать ключ", .key = 'a', .functionPtr = Controller::GenerateKey},
    {.name = "Шифровать",                  .key = 'b', .functionPtr = Controller::Encrypt    },
    {.name = "Дешифровать",              .key = 'c', .functionPtr = Controller::Descrypt   },
};

void Swap(Navigation::Item& firstItem, Navigation::Item& secondItem) {
    Navigation::Item temp = firstItem;
    firstItem = secondItem;
    secondItem = temp;
}

void NavigationItemsKeysQuickSort(Navigation::Item* navigationItems, size_t startedLeft, size_t startedRight) {
    long long left = static_cast<long long>(startedLeft);
    long long right = static_cast<long long>(startedRight);

    int pivot = static_cast<int>(navigationItems[(left + right) / 2].key);

    while (left <= right) {
        while (static_cast<int>(navigationItems[left].key) < pivot) {
            ++left;
        }

        while (static_cast<int>(navigationItems[right].key) > pivot) {
            --right;
        }

        if (left <= right) {
            Swap(navigationItems[left++], navigationItems[right--]);
        }
    }

    if (static_cast<long long>(startedLeft) < right) {
        NavigationItemsKeysQuickSort(navigationItems, startedLeft, right);
    }

    if (static_cast<long long>(startedRight) > left) {
        NavigationItemsKeysQuickSort(navigationItems, left, startedRight);
    }
}

Navigation::Item NavigationItemSearch(char key, Navigation::Item* navigationItems, size_t navigationItemsAmount) {
    long long left = 0;
    long long right = static_cast<long long>(navigationItemsAmount) - 1;

    while (left <= right) {
        long long middle = (left + right) / 2;

        if (navigationItems[middle].key == key) {
            return navigationItems[middle];
        } else if (static_cast<int>(navigationItems[middle].key) < static_cast<int>(key)) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return {};
}

void NavigationItemsPrint(Navigation::Item* navigationItems, size_t navigationItemsAmount) {
    std::cout << "Доступные действия:\n";

    for (size_t i = 0; i < navigationItemsAmount; i++) {
        if (navigationItems[i].key == 'q' || (navigationItems[i].functionPtr == nullptr && navigationItems[i].flagUsedFunctionPtr == nullptr)) {
            continue;
        }

        std::cout << navigationItems[i].key << " — " << navigationItems[i].name << '\n';
    }

    std::cout << "q — выход\n\n";
}
}  // namespace

namespace Navigation {

void Init(int argc, char** argv) {
    char userInput = ' ';

    Item navigationItems[kNavigationItemsAmount];

    for (size_t i = 0; i < kNavigationItemsAmount; i++) {
        navigationItems[i] = kNavigationItems[i];
    }

    while (userInput != 'q') {
        std::cout << "\x1B[2J\x1B[H";

        NavigationItemsKeysQuickSort(navigationItems, 0, kNavigationItemsAmount - 1);
        NavigationItemsPrint(navigationItems, kNavigationItemsAmount);

        std::cout << "Введите команду: ";
        std::cin >> userInput;

        if (userInput == 'q') {
            continue;
        }

        Item item = NavigationItemSearch(userInput, navigationItems, kNavigationItemsAmount);

        if (item.functionPtr) {
            item.functionPtr();
        } else if (item.flagUsedFunctionPtr) {
            item.flagUsedFunctionPtr(argc, argv);
        }

        if (item.functionPtr || item.flagUsedFunctionPtr) {
            std::cout << "\nПродолжить? (y/n): ";
            std::cin >> userInput;

            if (userInput != 'y') {
                break;
            }
        }
    }

    std::cout << "\nMeow ;)\n";
}
}  // namespace Navigation
