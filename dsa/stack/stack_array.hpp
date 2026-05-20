#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Stack {
private:
    T list[100];
    size_t sz = 0; // atua como top, indicando o índice do elemento no topo da pilha
public:
    bool empty();
    void push(T x);
    void pop();
    void top();
};

template <typename T>
bool Stack<T>::empty(){
    if (sz == 0) return true;

    return false;
}

template <typename T>
void Stack<T>::push(T x) {
    list[sz] = x;

    sz++;
}

template <typename T>
void Stack<T>::pop(){
    if (sz == 0) return;

    sz--;
}

template <typename T>
void Stack<T>::top() {
    if (sz > 0) { cout << list[sz-1] << endl; }
    else { cout << "PILHA VAZIA" << endl; }
}