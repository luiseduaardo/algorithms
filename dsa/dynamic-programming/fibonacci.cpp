#include <bits/stdc++.h>
#include <chrono>

using namespace std;

void preencher_vazio(int* l) {
    for (int i = 0; i < 10; i++) {
        l[i] = -1;
    }
}

// recursive
int rec_fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    return (rec_fibonacci(n-2) + rec_fibonacci(n-1));
}

// memoization (top-down)
int memo_fibonacci(int n, int* f) {
    if (n <= 1) {
        return n;
    }

    int x1, x2;
    if (f[n-1] != -1) {
        x1 = f[n-1];
    } else {
        x1 = memo_fibonacci(n-1, f);
    }

    if (f[n-2] != -1) {
        x2 = f[n-2];
    } else {
        x2 = memo_fibonacci(n-2, f);
    }

    int x = x1 + x2;
    f[n] = x;

    return x;
}

// tabulation (bottom-up)
int tabu_fibonacci(int n, int* f) {
    if (n <= 1) {
        return n;
    }

    f[0] = 0; f[1] = 1;

    for (int i = 2; i < n; i++) {
        f[i] = f[i-2] + f[i-1];
    }

    return f[n];
}

int main() {
    // chamada de fibonacci recursivo
    auto s_rec = chrono::steady_clock::now();
    int res1 = rec_fibonacci(40);
    auto e_rec = chrono::steady_clock::now();

    cout << "Resultado de fibonacci recursivo com memoização: " << res1 << endl;
    cout << "   Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(e_rec-s_rec).count() << "ns" << endl;

    // chamada de fibonacci recursivo com memoização
    auto s_memo = chrono::steady_clock::now();
    int* dict1 = new int[100];
    preencher_vazio(dict1);
    int res2 = memo_fibonacci(40, dict1);
    auto e_memo = chrono::steady_clock::now();
    cout << "Resultado de fibonacci recursivo: " << res1 << endl;
    cout << "   Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(e_memo-s_memo).count() << "ns" << endl;
    
    // chamada de fibonacci iterativo com tabulação
    auto s_tabu = chrono::steady_clock::now();
    int* dict2 = new int[100];
    preencher_vazio(dict2);
    int res3 = tabu_fibonacci(40, dict2);
    auto e_tabu = chrono::steady_clock::now();
    cout << "Resultado de fibonacci iterativo com tabulação: " << res1 << endl;
    cout << "   Tempo de execução: " << chrono::duration_cast<chrono::nanoseconds>(e_tabu-s_tabu).count() << "ns" << endl;

    return 0;
}