#include <iostream>
#define endl "\n"
#define spc " "

using namespace std;

int linear_search(int A[], int v, size_t size) {
    int idx = 0;

    while (idx <= size && A[idx] != v) {
        idx++;
    }

    return idx;
}

int main() {
    int A[15] = {3,6,8,12,14,17,25,29,31,36,42,47,53,55,62};
    size_t size = sizeof(A) / sizeof(A[0]) - 1;

    int target; cin >> target;

    int idx_1 = linear_search(A, target, size);

    if (idx_1 <= size) cout << "Elemento na posição " << idx_1 << ": " << A[idx_1] << endl;
    else cout << "Elemento não encontrado" << endl;

}