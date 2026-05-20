#include <bits/stdc++.h>
#define endl "\n";

using namespace std;


int height(int arr[], int qtd_elem, int index) {
    if (index > qtd_elem-1 || arr[index] == -1) return -1;

    int left_height = height(arr, qtd_elem, 2*index+1);
    int right_height = height(arr, qtd_elem, 2*index+2);

    int maximum = left_height >= right_height ? left_height : right_height;

    return 1 + maximum;
}

// se uma árvore é avl, todas suas subárvores também são
bool is_AVL(int arr[], int qtd_elem, int index) {
    if (index > qtd_elem-1 || arr[index] == -1) return true;

    int h_left = height(arr, qtd_elem, index*2+1);
    int h_right = height(arr, qtd_elem, index*2+2);

    int bf = h_right - h_left;

    if (bf == 1 || bf == 0 || bf == -1) {
        return is_AVL(arr, qtd_elem, index*2+1) && is_AVL(arr, qtd_elem, index*2+2);
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tree[100];
    int casos, qtde_elementos;
    cin >> casos;

    for (int i = 0; i < casos; i++) {
        cin >> qtde_elementos;

        for (int j = 0; j < qtde_elementos; j++) {
            cin >> tree[j];
        }

        cout << (is_AVL(tree, qtde_elementos, 0) ? "T" : "F") << endl;
    }

    return 0;
}