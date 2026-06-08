#include <iostream>
#include "graph.hpp"
#define endl '\n'
#define spc ' '

using namespace std;

int main() {
    Grafo g(8);

    g.adicionarAresta(0,1);
    g.adicionarAresta(0,2);
    g.adicionarAresta(0,3);
    g.adicionarAresta(1,0);
    g.adicionarAresta(1,5);
    g.adicionarAresta(2,1);
    g.adicionarAresta(2,6);
    g.adicionarAresta(3,1);
    g.adicionarAresta(3,7);
    g.adicionarAresta(6,5);
    g.adicionarAresta(6,7);
    g.adicionarAresta(7,5);

    g.dfs();

    return 0;
}