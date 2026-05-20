#include <bits/stdc++.h>
#define endl '\n'
#define spc ' '

using namespace std;

class Grafo {
private:
    struct No {
        int destino;
        No* prox;
    };

    int numVertices;
    No** listaAdj;
    No** tailAdj;

public:
    int* in_degree;

    Grafo(int vertices) {
        numVertices = vertices;
        listaAdj = new No*[vertices];
        tailAdj = new No*[vertices];
        in_degree = new int[vertices];

        for (int i = 0; i < vertices; i++) {
            listaAdj[i] = nullptr;
            tailAdj[i] = nullptr;
            in_degree[i] = 0;
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
        delete[] tailAdj;
        delete[] in_degree;
    }

    void adicionarAresta(int origem, int destino) {
        No* novo_no = new No{destino, nullptr};

        if (listaAdj[origem] == nullptr) {
            listaAdj[origem] = novo_no;
            tailAdj[origem] = novo_no;
        } else {
            tailAdj[origem]->prox = novo_no;
            tailAdj[origem] = novo_no;
        }
        
        in_degree[destino]++;
    }

    int contar_descendentes(int inicio) {
        bool* marcado = new bool[numVertices];
        int* fila = new int[numVertices];
        for (int i = 0; i < numVertices; i++) marcado[i] = false;

        int frente = 0, tras = 0;
        fila[tras++] = inicio;
        marcado[inicio] = true;
        int contagem = 0;

        while (frente < tras) {
            int v = fila[frente++];
            No* vizinho = listaAdj[v];
            while (vizinho != nullptr) {
                int u = vizinho->destino;
                if (!marcado[u]) {
                    marcado[u] = true;
                    contagem++;
                    fila[tras++] = u;
                }
                vizinho = vizinho->prox;
            }
        }
        delete[] marcado; delete[] fila;
        return contagem;
    }

    int distancia_bfs(int origem, int alvo) {
        if (origem == alvo) return 0;

        bool* marcado = new bool[numVertices];
        int* dist = new int[numVertices];
        int* fila = new int[numVertices];

        for (int i = 0; i < numVertices; i++) {
            marcado[i] = false;
            dist[i] = -1;
        }

        int frente = 0, tras = 0;
        fila[tras++] = origem;
        marcado[origem] = true;
        dist[origem] = 0;
        int resultado = -1;

        while (frente < tras) {
            int v = fila[frente++];
            if (v == alvo) {
                resultado = dist[v];
                break;
            }

            No* vizinho = listaAdj[v];
            while (vizinho != nullptr) {
                int u = vizinho->destino;
                if (!marcado[u]) {
                    marcado[u] = true;
                    dist[u] = dist[v] + 1;
                    fila[tras++] = u;
                }
                vizinho = vizinho->prox;
            }
        }
        delete[] marcado; delete[] dist; delete[] fila;
        return resultado;
    }

    void imprimir_arvore(int inicio, string nomes[]) {
        bool* marcado = new bool[numVertices];
        int* dist = new int[numVertices];
        int* fila = new int[numVertices];

        for (int i = 0; i < numVertices; i++) marcado[i] = false;

        int frente = 0, tras = 0;
        fila[tras++] = inicio;
        marcado[inicio] = true;
        dist[inicio] = 0;

        while (frente < tras) {
            int v = fila[frente++];

            if (dist[v] > 0) {
                cout << nomes[v] << " ";
                if (dist[v] == 1) cout << "filho\n";
                else if (dist[v] == 2) cout << "neto\n";
                else if (dist[v] == 3) cout << "bisneto\n";
                else cout << (dist[v] - 1) << "-neto\n";
            }

            No* vizinho = listaAdj[v];
            while (vizinho != nullptr) {
                int u = vizinho->destino;
                if (!marcado[u]) {
                    marcado[u] = true;
                    dist[u] = dist[v] + 1;
                    fila[tras++] = u;
                }
                vizinho = vizinho->prox;
            }
        }
        delete[] marcado; delete[] dist; delete[] fila;
    }
};

int total_pessoas = 0;
string array_nomes[10005];

int obter_id(string nome) {
    for(int i = 0; i < total_pessoas; i++) {
        if (array_nomes[i] == nome) {
            return i;
        }
    }
    array_nomes[total_pessoas] = nome;
    return total_pessoas++;
}

void printAncestral(int d, bool ancestral) {
    if (ancestral) {
        if (d == 1) cout << "pai\n";
        else if (d == 2) cout << "avo\n";
        else if (d == 3) cout << "bisavo\n";
        else cout << (d-1) << "-avo\n";
    } else {
        if (d == 1) cout << "filho\n";
        else if (d == 2) cout << "neto\n";
        else if (d == 3) cout << "bisneto\n";
        else cout << (d-1) << "-neto\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string pais[100005], filhos[100005];
    for (int i = 0; i < m; i++) {
        cin >> pais[i] >> filhos[i];
        obter_id(pais[i]);
        obter_id(filhos[i]);
    }

    Grafo g(total_pessoas);

    for (int i = 0; i < m; i++) {
        g.adicionarAresta(obter_id(pais[i]), obter_id(filhos[i]));
    }

    int max_descendentes = -1;
    int id_patriarca = -1;

    for (int i = 0; i < total_pessoas; i++) {
        if (g.in_degree[i] == 0) {
            int qtd = g.contar_descendentes(i);
            if (qtd > max_descendentes) {
                max_descendentes = qtd;
                id_patriarca = i;
            }
        }
    }

    if (id_patriarca != -1) {
        g.imprimir_arvore(id_patriarca, array_nomes);
    }

    int q; cin >> q;
    while (q--) {
        string a_nome, b_nome;
        cin >> a_nome >> b_nome;

        int a = obter_id(a_nome);
        int b = obter_id(b_nome);

        if (a == b) { // sem parentesco
            cout << "sem parentesco" << endl;
            continue;
        }

        int dist_desc = g.distancia_bfs(a, b);
            if (dist_desc != -1) {
                printAncestral(dist_desc, false);
            } else {
                int dist_anc = g.distancia_bfs(b, a);
                if (dist_anc != -1) {
                    printAncestral(dist_anc, true);
                } else {
                    cout << "sem parentesco\n";
                }
            }
    }

    return 0;
}