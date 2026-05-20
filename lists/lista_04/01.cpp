#include <iostream>
#define endl '\n'
#define spc ' '
#define INF 2147483647
#define ll long long

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

    int dijkstra(int origem, int destino, int* semaforo) {
        ll* dist = new ll[numVertices];
        bool* marcado = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            dist[i] = INF;
            marcado[i] = false;
        }

        dist[origem] = 0;

        for (int cont = 0; cont < numVertices - 1; cont++) {
            ll minDist = INF;
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

                if (!marcado[v] && dist[u] != INF && dist[u] + peso_aresta + semaforo[u] < dist[v]) {
                    dist[v] = dist[u] + peso_aresta + semaforo[u];
                }

                vizinho = vizinho->prox;
            }
        }

        int final = dist[destino];

        delete[] dist;
        delete[] marcado;

        return final;
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,s,t;
    cin >> n >> m >> s >> t;

    int semaforos[n+1];
    Grafo g(n+1);

    for (int i = 1; i <= n; i++) {
        cin >> semaforos[i];
    }

    int u,v,w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g.adicionarAresta(u,v,w);
    }

    int tempo_total = g.dijkstra(s, t, semaforos);

    if (tempo_total != INF) {
        cout << tempo_total << endl;
    } else {
        cout << "IMPOSSIVEL" << endl;
    }

    return 0;
}
