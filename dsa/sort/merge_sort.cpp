#include <bits/stdc++.h>
#define endl '\n'
#define spc ' '

using namespace std;

void merge(int A[], int low, int mid, int high) {
    int aux[high+1];
    int i = low;
    int j = mid+1;

    for (int cp = low; cp <= high; cp++) {
        aux[cp] = A[cp];
    }

    for (int k = low; k <= high; k++) {
        if (i < mid) {  // todos os elementos da esquerda já foram adicionados -> adiciona somente os da direita
            A[k] = aux[j];
            j++;
        } else if (j > high) { // todos os elementos da direita já foram adicionados -> adiciona somente os da esquerda
            A[k] = aux[i];
            i++;
        } else if (aux[i] > aux[j]) { // compara os elementos (elemento da esquerda é maior) -> adiciona o da direita
            A[k] = aux[j];
            j++;
        } else { // compara os elementos (elemento da direita é maior) -> adiciona o da esquerda
            A[k] = aux[i];
            i++;
        }
    }
}

void mergesort(int A[], int l, int h) {
    if (l < h) {
        int mid = (l+h)/2;

        mergesort(A, l, mid); // ordena a parte da esquerda
        mergesort(A, mid+1, h); // ordena a parte da direita

        merge(A, l, mid, h); // mistura a esquerda e a direita já ordenadas
    }
}

int main() {
    return 0;
}