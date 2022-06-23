/*
7_2. LSD для long long.
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 10^6. 
Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include <cassert>
#include <cstring>
#include <iostream>

const int BYTE = 8;

template<class T>
void SortLSD(T *array, int n) {
    for (unsigned int i = 0; i < sizeof(T); ++i) {
        CountingSort(array, n, [i](T num) { return (num >> BYTE * i) & 255; });
    }
}

template<class T, class TGetKey>
void CountingSort(T* array, int n, TGetKey getKey) {
	unsigned int max = getKey(array[0]);
	for(int i = 1; i < n; ++i) {
		if (max < getKey(array[i])) {
			max = getKey(array[i]);
		}
	}

	int *countArray = new int[max + 1];
	memset(countArray, 0, (max + 1) * sizeof(int));

	for(int i = 0; i < n; ++i)
		++countArray[getKey(array[i])];

	for(unsigned int i = 1; i <= max; ++i) {
		countArray[i] += countArray[i - 1];
	}

	T* tmpArray = new T[n];
	for(int i = n - 1; i >= 0; --i) {
		tmpArray[--countArray[getKey(array[i])]] = array[i];
	}
	delete[] countArray;
	for(int i = 0; i < n; ++i) {
		array[i] = tmpArray[i];
	}
	delete[] tmpArray;
}


void PrintArray(uint64_t *array, int size, std::ostream &outputStream) {
    for (int i = 0; i < size; ++i) {
        outputStream << array[i] << " ";
    }
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    int size = 0;
    assert(inputStream >> size);
    assert(size > 0);

    uint64_t *array = new uint64_t[size];

    for (int i = 0; i < size; ++i) {
        assert(inputStream >> array[i]);
    }

    SortLSD(array, size);

    PrintArray(array, size, outputStream);

    delete [] array;
}

int main()
{
    run(std::cin, std::cout);
	return 0;
}

