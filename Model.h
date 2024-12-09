#pragma once
#include "Key.h"

namespace Model {
void GenerateKey(Key *keys, int firstNum, int secondNum);
int Encrypt(int message, Key key);
int Descrypt(int message, Key key);
}  // namespace Model
