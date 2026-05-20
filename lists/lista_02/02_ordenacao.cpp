#include <bits/stdc++.h>
#define endl '\n'
#define spc ' '

using namespace std;

void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int A[], int low, int high) {
    int pivot = A[low];
    int i = low; int j =  high;

    while (i < j){
        do {
            i++;
        } while (A[i] <= pivot);

        do {
            j--;
        } while (A[j] > pivot);

        if (i < j) {
            swap(&A[i], &A[j]);
        }
    }

    swap(&A[low], &A[j]);

    return j;
}

void quicksort(int A[], int low, int high) {
    if (low < high) {
        int j = partition(A, low, high);
        quicksort(A, low, j);
        quicksort(A, j+1, high);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int len = 0; cin >> len;
    int arr[len];

    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    // função de sort
    quicksort(arr, 0, len);

    for (int i = 0; i < len; i++) {
        cout << arr[i] << endl;
    }

    return 0;
}
