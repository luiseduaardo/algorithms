#pragma once

#include <iostream>
#include "../linked-list/linked_list.hpp"
#define spc " "
#define endl "\n"

using namespace std;

template <typename T>
class Stack {
private:
    DoublyLinkedList<T> s;

public:
    bool empty() {
        if (s.get_first() == nullptr) return true;

        return false;
    }

    void push(T x) {
        s.insert(x);
    }

    void pop() {
        s.remove_last();
    }

    T top() {
        if (s.get_last()) {
            return s.get_last()->value;
        }
        return T();
    }
};