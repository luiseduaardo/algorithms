#include <iostream>
#define endl '\n'
#define ll long long

using namespace std;

class Grafo {
private:
    struct No {
        int destino;
        No* prox;
    };

    int numVertices;
    No** listaAdj;

public:
    Grafo(int vertices) {
        numVertices = vertices;
        listaAdj = new No*[vertices];

        for (int i = 0; i < vertices; i++) {
            listaAdj[i] = nullptr;
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
    }

    void adicionarAresta(int origem, int destino) {
        No* novo_no = new No{destino, listaAdj[origem]};
        listaAdj[origem] = novo_no;

        novo_no = new No{origem, listaAdj[destino]};
        listaAdj[destino] = novo_no;
    }

    ll dfs_protesto(int raiz, ll* pesos) {
        int* ordem_bfs = new int[numVertices];
        int* pai = new int[numVertices];
        int* fila = new int[numVertices];
        
        ll** dp = new ll*[numVertices];
        for (int i = 0; i < numVertices; i++) {
            dp[i] = new ll[2]{0, 0};
            pai[i] = -1;
        }

        int frente = 0, tras = 0;
        
        fila[tras++] = raiz;
        int index_ordem = 0;
        pai[raiz] = raiz;

        while (frente < tras) {
            int u = fila[frente++];
            ordem_bfs[index_ordem++] = u;

            No* vizinho = listaAdj[u];
            while (vizinho != nullptr) {
                int v = vizinho->destino;
                if (v != pai[u]) {
                    pai[v] = u;
                    fila[tras++] = v;
                }
                vizinho = vizinho->prox;
            }
        }

        for (int i = numVertices - 1; i >= 0; i--) {
            int u = ordem_bfs[i];

            dp[u][0] = 0;
            dp[u][1] = pesos[u];

            No* vizinho = listaAdj[u];
            while (vizinho != nullptr) {
                int v = vizinho->destino;
                
                if (v != pai[u]) {
                    dp[u][0] += ((dp[v][0] > dp[v][1]) ? dp[v][0] : dp[v][1]);
                    dp[u][1] += dp[v][0];
                }
                vizinho = vizinho->prox;
            }
        }

        ll resposta = ((dp[raiz][0] > dp[raiz][1]) ? dp[raiz][0] : dp[raiz][1]);

        delete[] ordem_bfs;
        delete[] pai;
        delete[] fila;
        for (int i = 0; i < numVertices; i++) {
            delete[] dp[i];
        }
        delete[] dp;

        return resposta;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, val;
    cin >> n;
    ll* w = new ll[n];

    for (int i = 0; i < n; i++) {
        cin >> val;
        w[i] = val;
    }

    Grafo g(n);
    int u, v;
    for (int i = 0; i < n-1; i++) {
        cin >> u >> v;
        g.adicionarAresta(u-1, v-1);
    }

    cout << g.dfs_protesto(0, w) << endl;

    return 0;
}
