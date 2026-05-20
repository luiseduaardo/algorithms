#include <bits/stdc++.h>
#include "deque.hpp"
#define endl "\n"
#define spc " "

using namespace std;

template <typename T>
class Deque {
private:
    static const size_t max_cap = 100;
    size_t sz = 0;
    size_t head = 0;
    size_t tail = -1;

    T list[max_cap];
public:
    void push_front(T x);
    void push_back(T x);
    T pop_front();
    T pop_back();
};

template <typename T>
void Deque<T>::push_front(T x) {
    head = (head - 1 + max_cap) % max_cap;
    list[head] = x;
}

template <typename T>
void Deque<T>::push_back(T x) {
    tail = (tail + 1) % max_cap;
    list[tail] = x;
}

template <typename T>
T Deque<T>::pop_front() {
    T valor = list[head];
    head = (head + 1) % max_cap;

    return valor;
}

template <typename T>
T Deque<T>::pop_back() {
    T valor = list[tail];
    tail = (tail - 1 + max_cap) % max_cap;

    return valor;
}