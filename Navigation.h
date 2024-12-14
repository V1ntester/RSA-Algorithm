#pragma once
#include <cstddef>

namespace Navigation {
struct Item {
    char name[256];
    char key;
    void (*functionPtr)() = nullptr;
    void (*flagUsedFunctionPtr)(int argc, char** argv) = nullptr;
};

void Init(int argc = 0, char** argv = nullptr);
}  // namespace Navigation
