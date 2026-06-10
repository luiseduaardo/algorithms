#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;

struct Item {
    int id_item;
    ll peso, valor;
};

ll max(ll a, ll b) {
    return (a > b) ? a : b;
}

// aplica o knapsack para calcular o valor ótimo
ll knapsack(int n, ll W, Item* itens, ll* dp) {
    for (int i = 0; i < n; i++) {
        for (ll j = W; j >= itens[i].peso; j--) {
            dp[j] = max(dp[j], dp[j - itens[i].peso] + itens[i].valor);
        }
    }
    return dp[W];
}

// ordenação dos itens em ordem decrescente
void sort(int n, Item* items) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            ll val1 = items[j].valor * items[j + 1].peso;
            ll val2 = items[j + 1].valor * items[j].peso;

            bool troca = false;
            
            if (val1 < val2) {
                troca = true; 
            } else if (val1 == val2) {
                if (items[j].id_item > items[j + 1].id_item) {
                    troca = true;
                }
            }

            if (troca) {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

// faz o cálculo do valor aproximado pela estratégia gulosa
ll aproximado(int n, ll W, ll M, Item* items) {
    sort(n, items);

    ll G = 0; // valor obtido pelo guloso
    ll peso_atual = 0;
    
    for (int i = 0; i < n; i++) {
        if (peso_atual + items[i].peso <= W) {
            peso_atual += items[i].peso;
            G += items[i].valor;
        }
    }

    return max(G, M);
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll W;
    cin >> n >> W;

    Item* itens = new Item[n];
    ll* dp = new ll[W+1]();
    ll M = 0; // maior valor de um único item que cabe na mochila

    for (int i = 0; i < n; i++) {
        cin >> itens[i].peso >> itens[i].valor;

        itens[i].id_item = i;
        
        if (itens[i].peso <= W) {
            M = max(M, itens[i].valor);
        }
    }

    ll val_optm = knapsack(n, W, itens, dp);
    ll val_aprox = aproximado(n, W, M, itens);

    std::cout << val_optm << " " << val_aprox << "\n";

    return 0;
}
