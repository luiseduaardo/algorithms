#include <iostream>
#define endl '\n'
#define spc ' '
#define INF 2147483647

using namespace std;

class Grafo {
private:
    struct No {
        int destino;
        int peso;
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

    void adicionarAresta(int origem, int destino, int peso = 1) {
        No* novo_no = new No{destino, peso, listaAdj[origem]};
        listaAdj[origem] = novo_no;

        novo_no = new No{origem, peso, listaAdj[destino]};
        listaAdj[destino] = novo_no;
    }

    int prim(int origem = 0) {
        int* dist = new int[numVertices];
        bool* marcado = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            dist[i] = INF;
            marcado[i] = false;
        }

        dist[origem] = 0;

        for (int cont = 0; cont < numVertices; cont++) {
            int minDist = INF;
            int u = -1;

            for (int v = 0; v < numVertices; v++) {
                if (!marcado[v] && dist[v] <= minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }

            if (u == -1) break;

            marcado[u] = true;

            No* vizinho = listaAdj[u];
            while (vizinho != nullptr) {
                int v = vizinho->destino;
                int peso_aresta = vizinho->peso;

                if (!marcado[v] && dist[u] != INF && peso_aresta < dist[v]) {
                    dist[v] = peso_aresta;
                }

                vizinho = vizinho->prox;
            }
        }

        int peso_total = 0;
        for (int i = 0; i < numVertices; i++) {
            peso_total += dist[i];
        }

        delete[] dist;
        delete[] marcado;

        return peso_total;
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, soma;
    cin >> n >> m;

    Grafo g(n+1);
    int geradores[n];

    for (int i = 1; i <= n; i++) {
        cin >> geradores[i];
        g.adicionarAresta(0, i, geradores[i]);
    }

    int u, v, c;
    while (m--) {
        cin >> u >> v >> c;
        g.adicionarAresta(u, v, c);
    }

    int soma_total = g.prim();

    cout << soma_total << endl;

    return 0;
}
