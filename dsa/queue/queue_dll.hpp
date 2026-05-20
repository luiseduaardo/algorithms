#include <bits/stdc++.h>
#include "../linked-list/linked_list.hpp"
#define endl "\n"
#define spc " "

using namespace std;

template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list;

public:
    // adicionar na tail
    void enqueue(T x) {
        list.insert(x);
    }

    // remover do head
    void dequeue() {
        list.remove(list.get_first()->value);
    }

    // head
    T front() {
        return list.get_first()->value;
    }

    // tail
    T back() {
        return list.get_last()->value;
    }
};