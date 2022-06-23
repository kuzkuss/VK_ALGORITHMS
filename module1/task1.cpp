/*
1.4 Инвертируйте значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K.
Формат выходных данных. Число с инвертированным битом в десятичном виде.
*/

#include <cassert>
#include <climits>
#include <iostream>

void invert(unsigned int &num, int bit) { 
  num ^= 1u << bit;
}

int main() {
  unsigned int num = 0;
  int bit = 0;

  assert(std::cin >> num >> bit);

  assert(bit >= 0 && bit <= 31);

  invert(num, bit);

  std::cout << num << std::endl;
  return 0;
}
