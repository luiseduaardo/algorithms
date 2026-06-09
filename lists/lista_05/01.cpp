#include <iostream>
#define endl '\n'
#define ll long long

using namespace std;

struct Palestra {
    int id_palestra, inicio, termino;
    long long valor;
};

// aplica meu quicksort antigo para ordenar as palestrar pelo término
void swap_palestra(Palestra *p1, Palestra* p2) {
    Palestra temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(Palestra A[], int low, int high) {
    int pivot = A[low + (high - low) / 2].termino;
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (A[i].termino < pivot);
        do { j--; } while (A[j].termino > pivot);

        if (i >= j) return j;
        
        swap_palestra(&A[i], &A[j]);
    }
}

void quicksort(Palestra A[], int low, int high) {
    if (low < high) {
        int p = partition(A, low, high);
        quicksort(A, low, p);
        quicksort(A, p + 1, high);
    } 
}

// função de recorrência já conhecida do problema do agendamento de compromissos
ll minhadp(Palestra* rest, int k) {
    if (k == 0) return 0;

    ll* dp = new ll[k + 1];
    dp[0] = 0;

    for (int i = 1; i <= k; i++) {
        int low = 0, high = i - 2; 
        int prev_idx = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (rest[mid].termino <= rest[i-1].inicio) {
                prev_idx = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        long long val = rest[i-1].valor;
        if (prev_idx != -1) {
            val += dp[prev_idx + 1];
        }

        dp[i] = (dp[i-1] > val) ? dp[i-1] : val; // aplica a função de recorrência - S(n) = max(S(n-1), v_n + S(p(n)))
    }
    
    return dp[k];
}

int main(int argc, char *argv[]) {
    // Otimização de I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    Palestra* pls = new Palestra[n + 1];
    bool* cancelado = new bool[n + 1];
    
    for (int i = 1; i <= n; i++) {
        cin >> pls[i].inicio >> pls[i].termino >> pls[i].valor;
        pls[i].id_palestra = i;
        cancelado[i] = false;
    }

    int qtd_cancelado = 0;
    int u, v;
    
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        if (!cancelado[u] && !cancelado[v]) {
            cancelado[u] = true;
            cancelado[v] = true;
            qtd_cancelado += 2;
        }
    }

    int qtd_restante = n - qtd_cancelado;
    Palestra* restantes = new Palestra[qtd_restante];
    
    for (int i = 1, j = 0; i <= n; i++) {
        if (!cancelado[i]) {
            restantes[j] = pls[i];
            j++;
        }
    }

    if (qtd_restante > 0) {
        quicksort(restantes, 0, qtd_restante - 1);
    }

    ll lucro_maximo = minhadp(restantes, qtd_restante);

    cout << qtd_cancelado << " " << lucro_maximo << endl;

    delete[] pls;
    delete[] cancelado;
    delete[] restantes;

    return 0;
}