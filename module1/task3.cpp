/*
3_3. Реализовать очередь с помощью двух стеков.
Требования: Очередь должна быть реализована в виде класса.
Стек тоже должен быть реализован в виде класса.
*/

#include <cassert>
#include <cstring>
#include <iostream>

const int STEP = 2;
const int POP_FRONT = 2;
const int PUSH_BACK = 3;

template <class T>
class Stack {
    public:
        explicit Stack() = default;
        explicit Stack(int size);
        ~Stack();

        Stack(const Stack &) = delete;
        Stack &operator=(const Stack &) = delete;

        T Pop();
        void Push(const T &value);
        bool IsEmpty() const { return top == -1; }
        int Size() const { return top + 1; }

    private:
        T *buffer = nullptr;
        int capacity = 0;
        int top = -1;
};

template<class T>
Stack<T>::Stack(int size) {
    buffer = new T[size];
    capacity = size;
    top = -1;
}

template<class T>
Stack<T>::~Stack() {
    delete [] buffer;
}

template<class T>
T Stack<T>::Pop() {
    assert(!IsEmpty());
    return buffer[top--];
}

template<class T>
void Stack<T>::Push(const T &value) {
    if (capacity <= top + 1) {
        T *tmpBuffer = buffer;
        buffer = new T[capacity * STEP];
        memmove(buffer, tmpBuffer, sizeof(T) * capacity);
        delete [] tmpBuffer;
        capacity *= STEP;
    }
    buffer[++top] = value;
}

template <class T>
class Queue {
    public:
        explicit Queue() = default;
        explicit Queue(int size) : pushStack(size), popStack(size) {}
        ~Queue() = default;

        void PushBack(const T &value);
        T PopFront();
        bool IsEmpty() const { return pushStack.IsEmpty() && popStack.IsEmpty(); }
    private:
        Stack<T> pushStack;
        Stack<T> popStack;
        void Move();
};

template <class T>
T Queue<T>::PopFront() {
    assert(!IsEmpty());
    if (popStack.IsEmpty()) {
        Move();
    }
    return popStack.Pop();
}

template <class T>
void Queue<T>::PushBack(const T &value) {
    pushStack.Push(value);
}

template<class T>
void Queue<T>::Move() {
    while (pushStack.Size() != 0) {
        popStack.Push(pushStack.Pop());
    }
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    int n;
    assert(inputStream >> n);
    assert(n > 0 && n <= 1000000);

    Queue<int> queue(n);

    bool result = true;
    for (int i = 0; i < n && result; ++i) {
        int action = 0;
        int value = 0;
        assert(inputStream >> action >> value);
        switch (action) {
            case POP_FRONT:
                if (queue.IsEmpty()) {
                    result = value == -1;
                    break;
                }
                result = queue.PopFront() == value;
                break;
            case PUSH_BACK:
                queue.PushBack(value);
                break;
            default:
                assert(false);
        }
    }

    outputStream << (result ? "YES" : "NO");
}

int main() {
    run(std::cin, std::cout);
    return 0;
}

