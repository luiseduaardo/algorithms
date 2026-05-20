#include <bits/stdc++.h>
#include "stack_array.hpp"
// #include "stack_dll.hpp"

using namespace std;

int main() {
    Stack<int> pilha;

    (pilha.empty()) ? cout << "TRUE" << endl : cout << "FALSE" << endl;

    pilha.push(1);
    pilha.push(2);
    pilha.push(3);
    pilha.push(4);

    pilha.top(); // 4
    (pilha.empty()) ? cout << "TRUE" << endl : cout << "FALSE" << endl;

    pilha.pop();
    pilha.top(); // 3
    pilha.pop();
    pilha.top(); // 2
    pilha.pop();
    pilha.top(); // 1
    pilha.pop();
    pilha.top(); //

    (pilha.empty()) ? cout << "TRUE" << endl : cout << "FALSE" << endl;

    return 0;
}