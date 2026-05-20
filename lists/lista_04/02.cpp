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

    int dijkstra(int origem, int* geradores) {
        int* dist = new int[numVertices];
        bool* marcado = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            dist[i] = INF;
            marcado[i] = false;
        }

        dist[origem] = 0;

        for (int cont = 0; cont < numVertices - 1; cont++) {
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

                if (!marcado[v] && dist[u] != INF && dist[u] + peso_aresta + geradores[u] < dist[v]) {
                    dist[v] = dist[u] + peso_aresta + geradores[u];
                }

                vizinho = vizinho->prox;
            }
        }

        int max_dist = -1;
        for (int i = 0; i < numVertices; i++) {
            if (dist[i] > max_dist) {
                max_dist = dist[i];
            }
        }

        delete[] dist;
        delete[] marcado;

        return max_dist;
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, soma;
    cin >> n >> m;

    Grafo g(n);
    int ger[n];

    for (int i = 0; i < n; i++) {
        cin >> ger[i];
    }

    int u, v, c;
    while (m--) {
        cin >> u >> v >> c;
        g.adicionarAresta(u, v, c);
    }

    int soma_total = -1, it;
    for (int i = 0; i < n; i++) {
        it = g.dijkstra(i, ger);
        if (it > soma_total) {
            soma_total = it;
        }
    }

    cout << soma_total << endl;

    return 0;
}
