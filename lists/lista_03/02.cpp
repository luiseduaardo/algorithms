#include <bits/stdc++.h>
#define endl '\n'

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

    int* bfs(int* postos, int num_postos) {
        int* distancia = new int[numVertices];
        int* fila = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            distancia[i] = -1;
        }

        int frente = 0, tras = 0;

        for (int i = 0; i < num_postos; i++) {
            int id_posto = postos[i];
            fila[tras++] = id_posto;
            distancia[id_posto] = 0;
        }

        while (frente < tras) {
            int v = fila[frente++];

            No* vizinho = listaAdj[v];
            while (vizinho != nullptr) {
                int u = vizinho->destino;
                
                if (distancia[u] == -1) {
                    distancia[u] = distancia[v] + 1;
                    fila[tras++] = u;
                }
                vizinho = vizinho->prox;
            }
        }

        delete[] fila;
        
        return distancia; 
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int linhas, colunas;
    cin >> linhas >> colunas;

    char** grid = new char*[linhas];
    for (int i = 0; i < linhas; i++) {
        grid[i] = new char[colunas];
        cin >> grid[i];
    }

    int totalVertices = linhas * colunas;
    Grafo grafo(totalVertices);

    int* postos = new int[totalVertices];
    int num_postos = 0;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int id_atual = i * colunas + j;

            if (grid[i][j] == 'P') {
                postos[num_postos++] = id_atual;
            }

            if (grid[i][j] != '#') {
                if (j + 1 < colunas && grid[i][j + 1] != '#') { // direita
                    int id_direita = i * colunas + (j + 1);
                    grafo.adicionarAresta(id_atual, id_direita);
                }
                
                if (i + 1 < linhas && grid[i + 1][j] != '#') { // baixo
                    int id_baixo = (i + 1) * colunas + j;
                    grafo.adicionarAresta(id_atual, id_baixo);
                }
            }
        }
    }

    int* distancias = grafo.bfs(postos, num_postos);

    int max_dist = -1;
    int pior_r = -1, pior_c = -1;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int id_atual = i * colunas + j;
            int d = distancias[id_atual];
            
            cout << d << (j == colunas - 1 ? "" : " ");

            if (d > max_dist) {
                max_dist = d;
                // coordenadas 1-indexadas!!!!
                pior_r = i+1;
                pior_c = j+1;
            }
        }
        cout << '\n';
    }

    cout << pior_r << " " << pior_c << " " << max_dist << '\n';

    delete[] distancias;
    delete[] postos;
    for (int i = 0; i < linhas; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
