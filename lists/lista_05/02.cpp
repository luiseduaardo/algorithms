#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;

struct Aresta {
    int u, v;
    ll peso;

    // aplicando a sobrecarga do operador < para aplicar a regra de desempate (menor peso, menor u, menor v)
    bool operator<(const Aresta& outra) const {
        if (peso != outra.peso) return peso < outra.peso;
        if (u != outra.u) return u < outra.u;
        return v < outra.v;
    }
};

// reaproveitando meu antigo merge sort
void merge(Aresta A[], int low, int mid, int high, Aresta aux[]) {
    int i = low;
    int j = mid + 1;

    for (int cp = low; cp <= high; cp++) {
        aux[cp] = A[cp];
    }

    for (int k = low; k <= high; k++) {
        if (i > mid) { 
            A[k] = aux[j];
            j++;
        } else if (j > high) { 
            A[k] = aux[i];
            i++;
        } 
        else if (aux[i] < aux[j]) { 
            A[k] = aux[i];
            i++;
        } else {
            A[k] = aux[j];
            j++;
        }
    }
}

void mergesort(Aresta A[], int l, int h, Aresta aux[]) {
    if (l < h) {
        int mid = l + (h - l) / 2;

        mergesort(A, l, mid, aux);
        mergesort(A, mid + 1, h, aux);

        merge(A, l, mid, h, aux);
    }
}

// reutilizando minha antiga classe de grafos
    // não havia implementado antes o kruskall e os sets
class Grafo {
private:
    struct No {
        int destino;
        No* prox;
    };

    int numVertices;
    No** listaAdj;
    int* pai;

    int findset(int v) {
        if (v == pai[v]) return v;
        return pai[v] = findset(pai[v]);
    }

    bool unionset(int u, int v) {
        int raizU = findset(u);
        int raizV = findset(v);
        if (raizU != raizV) {
            pai[raizV] = raizU;
            return true;
        }
        return false;
    }

    void dfs_rec(int v, bool* marcado, int* rota, int& contRota) {
        marcado[v] = true;
        rota[contRota++] = v;

        No* vizinho = listaAdj[v];
        while (vizinho != nullptr) {
            int u = vizinho->destino;
            if (!marcado[u]) {
                dfs_rec(u, marcado, rota, contRota);
            }
            vizinho = vizinho->prox;
        }
    }

public:
    Grafo(int vertices) {
        numVertices = vertices;
        listaAdj = new No*[vertices];
        pai = new int[vertices];

        for (int i = 0; i < vertices; i++) {
            listaAdj[i] = nullptr;
            pai[i] = i;
        }
    }

    ~Grafo() {
        for (int i = 0; i < numVertices; i++) {
            No* atual = listaAdj[i];
            while (atual != nullptr) {
                No* proximo = atual->prox;
                delete atual;
                atual = proximo;
            }
        }
        delete[] listaAdj;
        delete[] pai;
    }

    // insere e mantém em ordem crescente automaticamente
    void insert(int origem, int destino) {
        No* novo_no = new No{destino, nullptr};
        
        if (listaAdj[origem] == nullptr || listaAdj[origem]->destino > destino) {
            novo_no->prox = listaAdj[origem];
            listaAdj[origem] = novo_no;
        } else {
            No* atual = listaAdj[origem];
            while (atual->prox != nullptr && atual->prox->destino < destino) {
                atual = atual->prox;
            }
            novo_no->prox = atual->prox;
            atual->prox = novo_no;
        }
    }

    void kruskall(Aresta arestas[], int totalArestas) {
        for (int i = 0; i < totalArestas; i++) {
            if (unionset(arestas[i].u, arestas[i].v)) {
                insert(arestas[i].u, arestas[i].v);
                insert(arestas[i].v, arestas[i].u);
            }
        }
    }

    void dfs(int inicio, int* rota, int& contRota) {
        bool* marcado = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) marcado[i] = false;

        dfs_rec(inicio, marcado, rota, contRota);

        delete[] marcado;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;

    int maxArestas = (n * (n - 1)) / 2;
    if (maxArestas == 0) maxArestas = 1;

    Aresta* arestas = new Aresta[maxArestas];
    Aresta* merge = new Aresta[maxArestas];
    
    ll** matrizDist = new ll*[n + 1];
    for (int i = 0; i <= n; i++) {
        matrizDist[i] = new ll[n + 1]();
    }

    ll* tp_pausa = new ll[n + 1];
    ll* bonus = new ll[n + 1];
    int* rota = new int[n + 1];

    ll*** dp = new ll**[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new ll*[K + 1];
        for (int w = 0; w <= K; w++) {
            dp[i][w] = new ll[2];
        }
    }

    int totalArestas = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> matrizDist[i][j];
            if (i < j) {
                arestas[totalArestas].u = i;
                arestas[totalArestas].v = j;
                arestas[totalArestas].peso = matrizDist[i][j];
                totalArestas++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cin >> tp_pausa[i] >> bonus[i];
    }

    // aplicando o kruskall para gerar uma mst
    mergesort(arestas, 0, totalArestas - 1, merge); // ordenando as arestas
    Grafo mst(n + 1);
    mst.kruskall(arestas, totalArestas);

    // aplica a dfs em pré ordem para cancular o custo da rota
    int contRota = 0;
    mst.dfs(1, rota, contRota);

    ll custoTotalRota = 0;
    for (int i = 0; i < n - 1; i++) {
        custoTotalRota += matrizDist[rota[i]][rota[i+1]];
    }
    custoTotalRota += matrizDist[rota[n-1]][rota[0]];

    // pd
    ll maxBonus = 0;

    // caso ignoremos a primeira cidade
    for (int i = 0; i < n; i++)
        for (int w = 0; w <= K; w++)
            dp[i][w][0] = dp[i][w][1] = -1;

    dp[0][0][0] = 0;

    for (int i = 1; i < n; i++) {
        int cidadeAtual = rota[i];
        for (int w = 0; w <= K; w++) {
            ll melhorAnterior = -1;
            if (dp[i-1][w][0] != -1) melhorAnterior = dp[i-1][w][0];
            if (dp[i-1][w][1] != -1 && dp[i-1][w][1] > melhorAnterior) 
                melhorAnterior = dp[i-1][w][1];
            
            dp[i][w][0] = melhorAnterior;

            if (w >= tp_pausa[cidadeAtual] && dp[i-1][w - tp_pausa[cidadeAtual]][0] != -1) {
                dp[i][w][1] = dp[i-1][w - tp_pausa[cidadeAtual]][0] + bonus[cidadeAtual];
            }
        }
    }

    for (int w = 0; w <= K; w++) {
        if (dp[n-1][w][0] > maxBonus) maxBonus = dp[n-1][w][0];
        if (dp[n-1][w][1] > maxBonus) maxBonus = dp[n-1][w][1];
    }

    // passando obrigatoriamente pela primeira cidade
    for (int i = 0; i < n; i++)
        for (int w = 0; w <= K; w++)
            dp[i][w][0] = dp[i][w][1] = -1;

    if (tp_pausa[rota[0]] <= K) {
        dp[0][tp_pausa[rota[0]]][1] = bonus[rota[0]];
    }

    for (int i = 1; i < n; i++) {
        int cidadeAtual = rota[i];
        for (int w = 0; w <= K; w++) {
            ll melhorAnterior = -1;
            if (dp[i-1][w][0] != -1) melhorAnterior = dp[i-1][w][0];
            if (dp[i-1][w][1] != -1 && dp[i-1][w][1] > melhorAnterior) 
                melhorAnterior = dp[i-1][w][1];
            
            dp[i][w][0] = melhorAnterior;

            if (i == 1) continue;

            if (w >= tp_pausa[cidadeAtual] && dp[i-1][w - tp_pausa[cidadeAtual]][0] != -1) {
                dp[i][w][1] = dp[i-1][w - tp_pausa[cidadeAtual]][0] + bonus[cidadeAtual];
            }
        }
    }

    // como pegamos a primeira, não podemos pegar a última (consecutivas)
    for (int w = 0; w <= K; w++) {
        if (dp[n-1][w][0] > maxBonus) maxBonus = dp[n-1][w][0];
    }

    cout << custoTotalRota << " " << maxBonus << endl;

    return 0;
}