#include <iostream>
#include "graph.hpp"
#define endl '\n'
#define spc ' '

using namespace std;

int main() {
    Grafo g(6);

    g.adicionarAresta(0, 1, 4);
    g.adicionarAresta(0, 2, 1);
    g.adicionarAresta(1, 2, 2);
    g.adicionarAresta(1, 3, 1);
    g.adicionarAresta(2, 3, 5);
    g.adicionarAresta(3, 4, 3);

    g.dijkstra(0);

    return 0;
}