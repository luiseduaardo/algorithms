#include <iostream>
#define endl "\n"
#define spc " "

using namespace std;

int bin_search_iterative(int A[], int key, size_t sz) {
    int l, h; l = 0; h = sz;

    while (l <= h) {
        int mid = (l+h) / 2;

        if (key > A[mid]) {
            l = mid + 1;
        } else if (key < A[mid]) {
            h = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int bin_search_recursive(int A[], int l, int h, int key) {
    if (l == h) {
        if (A[l] == key) return l;

        return -1;
    }

    int mid = (l+h)/2;
    
    if (key > A[mid]) {
        return bin_search_recursive(A, mid+1, h, key);
    } else if (key < A[mid]) {
        return bin_search_recursive(A, l, mid-1, key);
    } else { 
        return mid;
    }
}

int main() {

    int A[15] = {3,6,8,12,14,17,25,29,31,36,42,47,53,55,62};
    size_t size = sizeof(A) / sizeof(A[0]) - 1;

    int target; cin >> target;

    /* IMPLEMENTAÇÃO ITERATIVA */
    cout << "Implementação iterativa:" << endl;

    int idx_1 = bin_search_iterative(A, target, size);

    if (idx_1 > -1) cout << "Elemento na posição " << idx_1 << ": " << A[idx_1] << endl;
    else cout << "Elemento não encontrado" << endl;

    /* IMPLEMENTAÇÃO RECURSIVA */

    cout << endl << "Implementação recursiva:" << endl;

    int idx_2 = bin_search_recursive(A, 0, size, target);

    if (idx_2 > -1) cout << "Elemento na posição " << idx_2 << ": " << A[idx_2] << endl;
    else cout << "Elemento não encontrado" << endl << endl;

    return 0;
}