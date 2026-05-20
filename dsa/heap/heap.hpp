#include <iostream>
#define inf 2147483647
#define spc " "
#define endl "\n"

using namespace std;

class Heap {
private:
    int heap[100];
    int sz;
    bool heap_quebrado;

    void swap(int *p1, int *p2) {
        int temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

    int parent(int k) {
        return (k-1)/2;
    }

    int left_chd(int k) {
        return 2*k+1;
    }

    int right_chd(int k) {
        return 2*k+2;
    }

    void max_heapify(int idx) {
        int maior, l, r; l = left_chd(idx); r = right_chd(idx); maior = idx;

        if (l < sz && heap[l] > heap[maior]) {
            maior = l;
        }

        if (r < sz && heap[r] > heap[maior]) {
            maior = r;
        }

        if (maior != idx) {
            swap(&heap[maior], &heap[idx]);
            max_heapify(maior); // faz o max heapify no que foi trocado
        }
    }

    void increase_key(int idx, int val) {
        if (val < heap[idx]) return;

        heap[idx] = val;
        while (idx > 0 && heap[parent(idx)] < heap[idx]) {
            swap(&heap[parent(idx)], &heap[idx]);
            idx = parent(idx);
        }
    }

public:
    Heap() {
        sz = 0;
        heap_quebrado = false;
    }

    void build_max_heap() {
        for (int i = sz/2 - 1; i >= 0; i--) {
            max_heapify(i);
        }

        heap_quebrado = false;
    }

    void insert(int val) {
        if (heap_quebrado) {
            build_max_heap();
        }

        heap[sz] = -inf;
        increase_key(sz, val);
        sz++;
    }

    // uma vez usado o heapsort, a classe deixa de ser uma heap e o objeto "morre"
    void heapsort() {
        int aux = sz;
        build_max_heap();

        for (int i = sz-1; i >= 1; i--) {
            swap(&heap[0], &heap[i]);
            sz--;
            max_heapify(0);
        }

        sz = aux;
        heap_quebrado = true;
    }

    void print_heap() {
        for (int i = 0; i < sz; i++) {
            cout << heap[i] << spc;
        }

        cout << endl;
    }
};