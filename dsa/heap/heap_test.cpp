#include <bits/stdc++.h>
#include "heap.hpp"
#define endl "\n"

using namespace std;

int main() {
    Heap hp;

    hp.insert(10);
    hp.insert(20);
    hp.insert(40);
    hp.insert(50);
    hp.insert(30);
    hp.insert(60);
    hp.insert(25);
    hp.insert(15);

    hp.print_heap();
    cout << endl;

    hp.heapsort();
    hp.print_heap();
    cout << endl;
}