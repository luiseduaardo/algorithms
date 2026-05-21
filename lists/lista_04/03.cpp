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
    }

    bool bfs_alcanca(bool* origens, int destino) {
        bool* marcado = new bool[numVertices];
        int* fila = new int[numVertices];
        int frente = 0, tras = 0;

        for (int i = 0; i < numVertices; i++) {
            marcado[i] = origens[i];
            if (origens[i]) {
                fila[tras++] = i;
            }
        }

        bool chegou = false;

        while (frente < tras) {
            int v = fila[frente++];

            if (v == destino) {
                chegou = true;
                break;
            }

            No* vizinho = listaAdj[v];
            while (vizinho != nullptr) {
                int u = vizinho->destino;
                if (!marcado[u]) {
                    marcado[u] = true;
                    fila[tras++] = u;
                }
                vizinho = vizinho->prox;
            }
        }

        delete[] marcado;
        delete[] fila;
        
        return chegou;
    }

    int bellman_ford(int origem, int destino) {
        int* dist = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            dist[i] = INF;
        }
        dist[origem] = 0;

        for (int i = 0; i < numVertices - 1; i++) {
            for (int u = 0; u < numVertices; u++) {
                No* vizinho = listaAdj[u];
                while (vizinho != nullptr) {
                    int v = vizinho->destino;
                    if (dist[u] + vizinho->peso < dist[v]) {
                        dist[v] = dist[u] + vizinho->peso;
                    }
                    vizinho = vizinho->prox;
                }
            }
        }

        // aqui eu verifico se existe algum ciclo
        bool* em_ciclo = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) em_ciclo[i] = false;
        bool achou_ciclo = false;

        for (int u = 0; u < numVertices; u++) {
            No* vizinho = listaAdj[u];
            while (vizinho != nullptr) {
                int v = vizinho->destino;
                if (dist[u] + vizinho->peso < dist[v]) {
                    em_ciclo[v] = true;
                    achou_ciclo = true;
                }
                vizinho = vizinho->prox;
            }
        }

        // caso eu tenha achado algum ciclo, aqui vai verificar se o ciclo vai de alguma forma impactar o caminho entre a origem e o destino
        if (achou_ciclo && bfs_alcanca(em_ciclo, destino)) {
            delete[] dist;
            delete[] em_ciclo;
            return -INF;
        }

        int d = dist[destino];

        delete[] dist;

        return d;
    }
};

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,s,t;
    cin >> n >> m >> s >> t;
    Grafo g(n);

    int u,v,w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        g.adicionarAresta(u-1, v-1, w);
    }

    int result = g.bellman_ford(s-1,t-1);

    if (result == INF) {
        cout << "IMPOSSIVEL" << endl;
    } else if (result == -INF) {
        cout << "ROTA INVALIDA" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
