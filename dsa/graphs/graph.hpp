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

    void dfs_rec(int v, int* antecessor, bool* marcado) {
        marcado[v] = true;

        No* vizinho = listaAdj[v];
        while (vizinho != nullptr) {
            int u = vizinho->destino;
            if (!marcado[u]) {
                antecessor[u] = v;
                dfs_rec(u, antecessor, marcado);
            }
            vizinho = vizinho->prox;
        }
    }

    void print_caminho(int v, int* antecessor) {
        if (v == -1) return;
        
        print_caminho(antecessor[v], antecessor);
        cout << v << " ";
    }

    void print_dijkstra(int origem, int* dist, int* antecessor) {
        cout << "Distancias da origem " << origem << " ate os outros vertices:" << endl;
        for (int i = 0; i < numVertices; i++) {
            if (dist[i] == INF) {
                cout << "Vertice " << i << ": Inacessivel" << endl;
            } else {
                cout << "Vertice " << i << ": Distancia = " << dist[i] << " | Caminho = ";
                print_caminho(i, antecessor);
                cout << endl;
            }
        }
    }

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

    void dfs() {
        bool* marcado = new bool[numVertices];
        int* antecessor = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            marcado[i] = false;
            antecessor[i] = -1;
        }

        for (int i = 0; i < numVertices; i++) {
            if (!marcado[i]) {
                dfs_rec(i, antecessor, marcado);
            }
        }

        cout << "Antecessores na DFS: ";
        for (int i = 0; i < numVertices; i++) cout << antecessor[i] << spc;
        cout << endl;

        delete[] marcado;
        delete[] antecessor;
    }

    void bfs() {
        bool* marcado = new bool[numVertices];
        int* antecessor = new int[numVertices];
        int* fila = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            marcado[i] = false;
            antecessor[i] = -1;
        }

        for (int i = 0; i < numVertices; i++) {
            if (!marcado[i]) {
                int frente = 0, tras = 0;
                
                fila[tras++] = i;
                marcado[i] = true;

                while (frente < tras) {
                    int v = fila[frente++];

                    No* vizinho = listaAdj[v];
                    while (vizinho != nullptr) {
                        int u = vizinho->destino;
                        if (!marcado[u]) {
                            marcado[u] = true;
                            antecessor[u] = v;
                            fila[tras++] = u;
                        }
                        vizinho = vizinho->prox;
                    }
                }
            }
        }

        cout << "Antecessores na BFS: ";
        for (int i = 0; i < numVertices; i++) cout << antecessor[i] << " ";
        cout << endl;

        delete[] marcado;
        delete[] antecessor;
        delete[] fila;
    }

    void dijkstra(int origem) {
        int* dist = new int[numVertices];
        bool* marcado = new bool[numVertices];
        int* antecessor = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            dist[i] = INF;
            marcado[i] = false;
            antecessor[i] = -1;
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

                if (!marcado[v] && dist[u] != INF && dist[u] + peso_aresta < dist[v]) {
                    dist[v] = dist[u] + peso_aresta;
                    antecessor[v] = u;
                }

                vizinho = vizinho->prox;
            }
        }

        print_dijkstra(origem, dist, antecessor);

        delete[] dist;
        delete[] marcado;
        delete[] antecessor;
    }
};