/*
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, 
и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости
*/

#include <cassert>
#include <cstring>
#include <iostream>

const int STEP = 2;

template <class T, class Compare>
class Heap {
 public:
  explicit Heap(Compare _cmp = Compare()) { cmp = _cmp; }
  explicit Heap(T *arr, size_t _size, Compare _cmp = Compare());

  ~Heap();

  Heap(const Heap &) = delete;

  Heap &operator=(const Heap &) = delete;

  T ExtractMin();
  void Pop();
  const T &PeekMin() const { return buffer[0]; }
  void Insert(const T &value);
  size_t Size() const { return size; }
  bool IsEmpty() const { return size == 0; }
  void Print(std::ostream &outputStream) const;
  void Sort();

 private:
  T *buffer = nullptr;
  size_t size = 0;
  size_t capacity = 0;
  Compare cmp;

  void SiftDown(size_t index);
  void SiftUp(size_t index);
  void BuildHeap();
};

template <class T, class Compare>
Heap<T, Compare>::Heap(T *arr, size_t _size, Compare _cmp) {
  buffer = new T[_size];
  memmove(buffer, arr, sizeof(T) * _size);
  size = _size;
  capacity = _size;
  cmp = _cmp;

  BuildHeap();
}

template <class T, class Compare>
Heap<T, Compare>::~Heap() {
  delete[] buffer;
}

template <class T, class Compare>
void Heap<T, Compare>::Print(std::ostream &outputStream) const {
  for (int i = size - 1; i >= 0; --i) {
    outputStream << buffer[i];
  }
}

template <class T, class Compare>
void Heap<T, Compare>::Sort() {
  size_t tmpSize = size;
  for (int i = size - 1; i >= 0; --i) {
    std::swap(buffer[i], buffer[0]);
    --size;
    SiftDown(0);
  }
  size = tmpSize;
}

template <class T, class Compare>
T Heap<T, Compare>::ExtractMin() {
  assert(!IsEmpty());

  T root = buffer[0];
  buffer[0] = buffer[size - 1];

  Pop();

  if (!IsEmpty()) {
    SiftDown(0);
  }

  return root;
}

template <class T, class Compare>
void Heap<T, Compare>::Pop() {
  assert(!IsEmpty());
  --size;
}

template <class T, class Compare>
void Heap<T, Compare>::SiftDown(size_t index) {
  while (index < size / 2) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    if (cmp(buffer[left], buffer[index])) {
      smallest = left;
    }
    if (right < size && cmp(buffer[right], buffer[smallest])) {
      smallest = right;
    }
    if (smallest == index) {
      break;
    }
    std::swap(buffer[index], buffer[smallest]);
    index = smallest;
  }
}

template <class T, class Compare>
void Heap<T, Compare>::SiftUp(size_t index) {
  while (index > 0) {
    size_t parent = (index - 1) / 2;
    if (!cmp(buffer[index], buffer[parent])) {
      break;
    }
    std::swap(buffer[parent], buffer[index]);
    index = parent;
  }
}

template <class T, class Compare>
void Heap<T, Compare>::BuildHeap() {
  for (int i = size / 2 - 1; i >= 0; --i) {
    SiftDown(i);
  }
}

template <class T, class Compare>
void Heap<T, Compare>::Insert(const T &value) {
  if (capacity <= size) {
    T *tmpBuffer = buffer;
    buffer = new T[capacity * STEP];
    memmove(buffer, tmpBuffer, sizeof(T) * capacity);
    delete [] tmpBuffer;
    capacity *= STEP;
  }
  buffer[size] = value;
  ++size;
  SiftUp(size - 1);
}

struct User {
  int id;
  int visits;

  User() = default;
  ~User() = default;
};

std::ostream &operator<<(std::ostream &os, const User &user) {
  return os << user.id << " ";
}

class UserIsLess {
 public:
  bool operator()(const User &l, const User &r) { return l.visits < r.visits; }
};

void findMaxUsers(Heap<User, UserIsLess> &heap, const User *usersArray,
                  size_t size) {
  UserIsLess isLess;
  for (size_t i = heap.Size(); i < size; ++i) {
    if (isLess(heap.PeekMin(), usersArray[i])) {
      heap.ExtractMin();
      heap.Insert(usersArray[i]);
    }
  }
}

void readUsers(std::istream &inputStream, User *users, size_t N) {
  for (size_t i = 0; i < N; ++i) {
    assert(inputStream >> users[i].id >> users[i].visits);
    assert(users[i].id >= 0 && users[i].visits >= 0);
  }
}

void run(std::istream &inputStream, std::ostream &outputStream) {
  size_t N;
  size_t K;

  assert(std::cin >> N >> K);
  assert(N > 0 && K > 0);

  User *usersArray = new User[N];

  readUsers(inputStream, usersArray, N);

  Heap<User, UserIsLess> heap(usersArray, K);

  findMaxUsers(heap, usersArray, N);

  heap.Sort();
  heap.Print(outputStream);

  delete[] usersArray;
}

int main() {
  run(std::cin, std::cout);
  return 0;
}