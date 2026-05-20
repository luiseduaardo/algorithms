/*
1) Transforme os vetores abaixo em heaps de máximo:
a) [3, 10, 40, 1, 60, 34, 21, 100, 5, 31, 2, 4, 6]
b) [100, 90, 80, 70, 60, 50, 40, 30, 20, 11, 1001]
c) [1, 2, 3, 9, 8, 7, 6, 5, 4, 20, 30, 40, 50, 60]
*/

#include <iostream>
#define spc " "
#define endl "\n"

using namespace std;

#include <bits/stdc++.h>

using namespace std;

int parent(int i) {
    return floor(i/2);
}

int left(int i) {
    return 2*i+1;
}

int right(int i) {
    return 2*i+2;
}

void swap(int l[], int* p1, int* p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void max_heapify(int list[], int k, size_t length) {
    int l, r; l = left(k); r = right(k);
    int maior = k;

    if (l <= length && list[l] > list[k]) {
        maior = l;
    }

    if (l <= length && list[r] > list[k]) {
        maior = r;
    }

    if (maior != k) {
        swap(list, &list[k], &list[maior]);
        max_heapify(list, maior, length);
    }
}

void build_max_heap(int list[], size_t len) {
    for (int i = len/2; i > 0; i--) {
        max_heapify(list, i, len);
    }
}

void print_list(int list[], size_t len) {
    for (int i = 0; i < len; i++) {
        cout << list[i] << spc;
    }

    cout << endl;
}

int main() {
    int list_a[] = {3, 10, 40, 1, 60, 34, 21, 100, 5, 31, 2, 4, 6};
    size_t len_a = sizeof(list_a) / sizeof(list_a[0]);

    cout << "Antes do max-heapify: ";
    print_list(list_a, len_a);
    build_max_heap(list_a, len_a);
    cout << "Depois do max-heapify: ";
    print_list(list_a, len_a);
    cout << endl;

    int list_b[] = {3, 10, 40, 1, 60, 34, 21, 100, 5, 31, 2, 4, 6};
    size_t len_b = sizeof(list_b) / sizeof(list_b[0]);

    cout << "Antes do max-heapify: ";
    print_list(list_b, len_b);
    build_max_heap(list_b, len_b);
    cout << "Depois do max-heapify: ";
    print_list(list_b, len_b);
    cout << endl;

    int list_c[] = {3, 10, 40, 1, 60, 34, 21, 100, 5, 31, 2, 4, 6};
    size_t len_c = sizeof(list_c) / sizeof(list_c[0]);

    cout << "Antes do max-heapify: ";
    print_list(list_c, len_c);
    build_max_heap(list_c, len_c);
    cout << "Depois do max-heapify: ";
    print_list(list_c, len_c);
    cout << endl;

    return 0;
}