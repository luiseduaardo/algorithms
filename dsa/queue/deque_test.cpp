#include <bits/stdc++.h>
#include "deque.hpp"
#define endl "\n"
#define spc " "

using namespace std;

int main() {
    Deque<int> dq;

    dq.push_back(10);
    dq.push_front(20);
    dq.push_back(30);

    cout << "pop_front: " << dq.pop_front() << endl;
    cout << "pop_back: " << dq.pop_back() << endl;
    cout << "pop_front: " << dq.pop_front() << endl;

    return 0;
}