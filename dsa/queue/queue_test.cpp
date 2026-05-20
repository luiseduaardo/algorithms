#include <bits/stdc++.h>
// #include "queue_array.hpp"
#include "queue_dll.hpp"
#define endl "\n"
#define spc " "

using namespace std;


int main() {
    // AI-generated cases
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    cout << "Queue after enqueue 10, 20, 30: front=" << q.front() << ", back=" << q.back() << endl;

    q.dequeue();
    cout << "After one dequeue: front=" << q.front() << ", back=" << q.back() << endl;

    q.dequeue();
    q.dequeue();
    q.enqueue(40);
    cout << "After dequeuing all and enqueue 40: front=" << q.front() << ", back=" << q.back() << endl;

    Queue<string> names;
    names.enqueue("Alice");
    names.enqueue("Bob");
    cout << "String queue: front=" << names.front() << ", back=" << names.back() << endl;

    return 0;
}