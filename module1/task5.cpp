/*
5_3. Закраска прямой 1.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri).
Найти длину окрашенной части числовой прямой.
*/

#include <cassert>
#include <cstring>
#include <iostream>

struct Point {
    int x;
    int shadeChange;

    Point() = default;
    ~Point() = default;
};

template<class T>
class Comparator {
    public:
        bool operator()(const T &left, const T &right) { return left < right; }
};

class PointComparator {
public:
	bool operator()(const Point& left, const Point& right) { return left.x < right.x; }
};

template<class T, class Compare = Comparator<T>>
void merge(T *array, int left, int mid, int right, Compare cmp = Comparator<T>()) {
    T *mergeArray = new T[right - left + 1];
    int iLeft = left;
    int iRight = mid;
    int iRes = 0;
    while (iLeft < mid && iRight < right) {
        if (cmp(array[iLeft], array[iRight])) {
            mergeArray[iRes] = array[iLeft];
            ++iLeft;
            ++iRes;
        } else {
            mergeArray[iRes] = array[iRight];
            ++iRight;
            ++iRes;
        }
    }
    while (iLeft < mid) {
        mergeArray[iRes] = array[iLeft];
        ++iLeft;
        ++iRes;
    }
    while (iRight < right) {
        mergeArray[iRes] = array[iRight];
        ++iRight;
        ++iRes;
    }
    for (int i = left; i < right; ++i) {
        array[i] = mergeArray[i - left];
    }
    delete [] mergeArray;
}

template<class T, class Compare = Comparator<T>>
void mergeSort(T *array, int size, Compare cmp = Comparator<T>()) {
    for (int i = 1; i < size; i += i) {
        for (int j = 0; j < size - i; j += i + i) {
            int left = j;
            int mid = j + i;
            int right = j + i + i;
            if (right >= size) {
                right = size;
            }
            merge(array, left, mid, right, cmp);
        }
    }
}

int countLen(Point *array, int size) {
    int totalShade = array[0].shadeChange;
    int shadedLen = 0;
    for (int i = 1; i < size; ++i) {
        if (totalShade > 0) {
            shadedLen += array[i].x - array[i - 1].x;
        }
        totalShade += array[i].shadeChange;
    }
    return shadedLen;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    int N = 0;
    assert(inputStream >> N);
    assert(N > 0 && N <= 10000);

    Point *pointsArray = new Point[2 * N];

    int j = 0;
    for (int i = 0; i < N; ++i) {
        assert(inputStream >> pointsArray[j].x >> pointsArray[j + 1].x);
        pointsArray[j].shadeChange = 1;
        pointsArray[j + 1].shadeChange = -1;
        j += 2;
    }

    mergeSort(pointsArray, 2 * N, PointComparator());

    int shadedLen = countLen(pointsArray, 2 * N);

    outputStream << shadedLen;

    delete [] pointsArray;
}

int main() {
    run(std::cin, std::cout);
    return 0;
}

