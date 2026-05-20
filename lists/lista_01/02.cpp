#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

class LinkedList {
private:
    struct Node {
        int value;
        int time;
        Node* next = nullptr;
    };

    Node* head; // nó sentinela

public:
    LinkedList();
    ~LinkedList();

    size_t size();
    void insert_team(int value, int team);
    int remove(size_t pos);
};

LinkedList::LinkedList() {
    head = new Node;
    head->next = nullptr;
}

LinkedList::~LinkedList() {
    Node* cur = head;
    Node* next;

    while (cur != nullptr) {
        next = cur->next;
        delete cur;
        cur = next;
    }
}

size_t LinkedList::size() {
    Node* cur = head;
    size_t sz = 0;

    while (cur->next != nullptr) {
        cur = cur->next;
        sz++;
    }

    return sz;
}

void LinkedList::insert_team(int value, int team) {
    Node* cur = head;
    Node* last_teamate = cur;

    Node* tail = head;

    while (cur != nullptr) {
        if (cur->time == team) { last_teamate = cur; }
        
        tail = cur;
        cur = cur->next;
    }

    Node* newnode = new Node;
    newnode->time = team;
    newnode->value = value;

    if (last_teamate == head) {
        tail->next = newnode;
    } else {
        newnode->next = last_teamate->next;
        last_teamate->next = newnode;
    }
}

int LinkedList::remove(size_t pos) {
    if (!(pos <= size())) { return NULL; }

    Node* cur = head;
    int i = 0;

    while (cur->next != nullptr && i < pos) {
        cur = cur->next;
        i++;
    }

    Node* todie = cur->next;
    cur->next = todie->next;
    int value = todie->value;

    delete todie;

    return value;
}

class Queue {
private:
    LinkedList ll;
public:
    void enqueue(int value, int time);
    int dequeue();
};

void Queue::enqueue(int value, int time) {
    ll.insert_team(value, time);
}

int Queue::dequeue() {
    return ll.remove(0);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int scenario, times, valor, elementos_time, elemento;
    int times_elementos[1000000];
    string operacao;
    Queue fila;
    scenario = 1;
    times = -1;

    while (1) {
        cin >> times;
        if (times == 0) { break; }

        // distribuição dos elementos pelos times numa array gigante (muito custo em memória (???))
            // array[elemento] é o time que ele pertence
        for (int i = 0; i < times; i++) {
            cin >> elementos_time;
            for (int k = 0; k < elementos_time; k++) {
                cin >> elemento;
                times_elementos[elemento] = i+1;
            }
        }

        cout << "Scenario #" << scenario << endl;

        while (1) {
            cin >> operacao;

            if (operacao == "ENQUEUE") {
                cin >> valor;
                fila.enqueue(valor, times_elementos[valor]);
            } else if (operacao == "DEQUEUE") {
                cout << fila.dequeue() << endl;
            } else if (operacao == "STOP") { break; }
        }

        cout << endl;
        
        scenario++;
    }
}