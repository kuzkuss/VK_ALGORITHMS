/*
6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <cassert>
#include <iostream>
using std::swap;

template<class T>
class isGreater {
public:
    bool operator()(const T &left, const T &right) { return left > right; }
};

template<class T, class Compare = isGreater<T>>
int Partition(T* array, int ileft, int iright, Compare cmp = isGreater<T>()) {
	if( iright - ileft <= 1 ) {
		return ileft;
	}

    int ipivot = ileft + rand() % (iright - ileft);
    swap(array[ipivot], array[iright - 1]);

	T pivot = array[iright - 1];
	int i = iright - 2;
	int j = i;
    for(; i >= ileft; --i) {
        if (cmp(array[i], pivot)) {
			swap(array[i], array[j--]);
		}
    }
	swap(array[j + 1], array[iright - 1]);
	return j + 1;
}

template<class T, class Compare = isGreater<T>>
T FindKStat(T* array, int ileft, int iright, int k, Compare cmp = isGreater<T>()) {
	int pivotPos = 0;
    do {
        pivotPos = Partition(array, ileft, iright, cmp);
        if (k > pivotPos) {
            ileft = pivotPos + 1;
        } else if (k < pivotPos) {
            iright = pivotPos;
        }
    } while(pivotPos != k);

	return array[pivotPos];
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    int amount = 0;
    assert(inputStream >> amount);
    assert(amount > 0);

    int *array = new int[amount];

    for (int i = 0; i < amount; ++i) {
        assert(inputStream >> array[i]);
    }

    outputStream << FindKStat(array, 0, amount, amount / 10) << std::endl;
    outputStream << FindKStat(array, 0, amount, amount / 2) << std::endl;
    outputStream << FindKStat(array, 0, amount, amount * 0.9) << std::endl;

    delete [] array;
}

int main()
{
    run(std::cin, std::cout);
	return 0;
}