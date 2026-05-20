#include <bits/stdc++.h>
#define endl "\n"
#define spc " "

using namespace std;

template <typename T>
class Queue {
private:
    static const size_t max_cap = 100;
    size_t sz = 0;
    size_t head = 0;
    size_t tail = 0;

    T list[max_cap];
public:
    void enqueue(T x);
    void dequeue();
    T front();
    T back();
};

template <typename T>
void Queue<T>::enqueue(T x) {
    list[tail] = x;

    if (tail == max_cap - 1) {
        tail = 0;
    } else {
        tail++;
    }

    sz++;
}

template <typename T>
void Queue<T>::dequeue() {
    if (sz == 0) return;

    if (head == max_cap - 1) {
        head = 0;
    } else {
        head++;
    }

    sz--;
}

template <typename T>
T Queue<T>::front() {
    return list[head];
}

template <typename T>
T Queue<T>::back() {
    return list[(tail == 0 ? max_cap - 1 : tail - 1)];
}