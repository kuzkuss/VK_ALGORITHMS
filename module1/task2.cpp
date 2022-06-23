/*
2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
Найти m за O(log m). Требования:  Время работы O(log m). Внимание! В этой задаче
сначала нужно определить диапазон бинарного поиска размером порядка m с помощью
экспоненциального поиска, а потом уже в нем делать бинарный поиск.

2 ≤ n ≤ 10000.
*/

#include <cassert>
#include <iostream>

int binarySearch(const int *array, int num, int start, int end) {
  int mid = (start + end) / 2;
  while (start <= end) {
    if (mid + 1 >= num) {
      if (array[mid - 1] > array[mid]) {
        --mid;
      }
      break;
    } else if (array[mid - 1] < array[mid] && array[mid] < array[mid + 1]) {
      start = mid + 1;
    } else if (array[mid - 1] > array[mid] && array[mid] > array[mid + 1]) {
      end = mid - 1;
    } else if (array[mid - 1] < array[mid] && array[mid] > array[mid + 1]) {
      break;
    } else {
      assert(false);
    }
    mid = (start + end) / 2;
  }
  return mid;
}

int exponentialSearch(const int *array, int num) {
  int ascendingPart = 1;
  int descendingPart = ascendingPart * 2;
  while (descendingPart < num - 1 &&
         array[ascendingPart - 1] < array[ascendingPart]) {
    if (array[descendingPart] > array[descendingPart + 1]) {
      break;
    }
    ascendingPart = descendingPart;
    descendingPart *= 2;
  }

  if (descendingPart > num - 1) {
    descendingPart = num - 1;
  }

  return binarySearch(array, num, ascendingPart - 1, descendingPart + 1);
}

void readArray(std::istream &inputStream, int num, int *array) {
  for (int i = 0; i < num; ++i) {
    assert(inputStream >> array[i]);
  }
}

void run(std::istream &inputStream, std::ostream &output) {
  int num = 0;
  inputStream >> num;

  assert(num >= 2 && num <= 10000);

  int *array = new int[num];

  readArray(inputStream, num, array);

  output << exponentialSearch(array, num) << std::endl;

  delete [] array;
}

int main() {
  run(std::cin, std::cout);
  return 0;
}

