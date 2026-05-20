#include <bits/stdc++.h>
#define endl '\n'
#define spc ' '
#define ht_size 400009
#define ll long long

using namespace std;

#include <iostream>

using namespace std;

// aplica a sobrecarga de operadores à struct pra não mudar na minha implementação original da AVL
struct InfoReagente {
    int quantidade;
    string nome;

    InfoReagente() : quantidade(0), nome("") {}
    InfoReagente(int q, string s) : quantidade(q), nome(s) {}
    
    bool operator<(const InfoReagente& outro) const {
        if (quantidade != outro.quantidade) {
            return quantidade < outro.quantidade;
        }

        return nome < outro.nome; 
    }

    bool operator>(const InfoReagente& outro) const {
        if (quantidade != outro.quantidade) {
            return quantidade > outro.quantidade;
        }
        return nome > outro.nome;
    }
    
    bool operator==(const InfoReagente& outro) const {
        return quantidade == outro.quantidade && nome == outro.nome;
    }
};

class AVL {
private:
    struct Node {
        InfoReagente data;
        int height; // altura máxima do meu nó até uma folha
        Node* left;
        Node* right;
        Node* parent;

        Node(InfoReagente d) : data(d), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void iorec(Node* node, int k, bool& achou) {
        if (node == nullptr) return;

        if (node->data.quantidade > k) {
            iorec(node->left, k, achou);
            return;
        }

        iorec(node->left, k, achou);
        
        cout << node->data.nome << spc << node->data.quantidade << endl;
        achou = true;
        
        iorec(node->right, k, achou);
    }

    int get_altura(Node* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    int get_fator_balanceamento(Node* n) {
        if (n == nullptr) return 0;
        return get_altura(n->right) - get_altura(n->left);
    }

    void atualizar_altura(Node* n) {
        if (n != nullptr) {
            int alt_esq = get_altura(n->left);
            int alt_dir = get_altura(n->right);

            int max = (alt_esq > alt_dir) ? alt_esq : alt_dir;

            n->height = 1 + max;
        }
    }

    void rotate_left(Node* x) {
        Node* y = x->right; // é o filho a direita que vai subir

        // filho a esquerda de Y passa a ser o filho a direita de X
        x->right = y->left;
        if (y->left) {
            y->left->parent = x;
        }

        // Y assume o lugar de X (muda a referência do pai de X)
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        // X vira filho a direita de Y
        y->left = x;
        x->parent = y;

        atualizar_altura(x);
        atualizar_altura(y);
    }

    void rotate_right(Node* x) {
        Node* y = x->left;

        x->left = y->right;
        if (y->right) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;

        atualizar_altura(x);
        atualizar_altura(y);
    }

    void balance(Node* n) {
        int bf = get_fator_balanceamento(n);
        
        if (bf == 2) {
            if (get_fator_balanceamento(n->right) > 0) { // rotação simples (mesmo sinal)
                rotate_left(n);
            } else { // rotação dupla (sinais trocados)
                rotate_right(n->right);
                rotate_left(n);
            }
        } else if (bf == -2) {
            if (get_fator_balanceamento(n->left) < 0) { // rotação simples (mesmo sinal)
                rotate_right(n);
            } else { // rotação dupla (sinais trocados)
                rotate_left(n->left);
                rotate_right(n);
            }
        }
    }

    void transplante(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }

        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    Node* min(Node* no) {
        Node* cur = no;

        while (cur->left != nullptr) {
            cur = cur->left;
        }

        return cur;
    }

public:
    AVL() {
        root = nullptr;
    }

    void insert(InfoReagente x) {
        Node* cur = root;
        Node* y = nullptr;

        while (cur != nullptr) {
            y = cur;

            if (cur->data > x) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }

        Node* newnode = new Node(x);
        newnode->parent = y;

        if (y == nullptr) {
            root = newnode;
        } else if (newnode->data > y->data) {
            y->right = newnode;
        } else {
            y->left = newnode;
        }

        while (y != nullptr) {
            atualizar_altura(y);
            balance(y);

            y = y->parent;
        }
    }

    Node* search(InfoReagente k) {
        Node* cur = root;

        while (cur != nullptr) {
            if (k > cur->data) {
                cur = cur->right;
            } else if (k < cur->data) {
                cur = cur->left;
            } else {
                return cur;
            }
        }

        return nullptr;
    }

    void delete_node(InfoReagente k) {
        Node* todie = search(k);
        
        if (todie == nullptr) return;

        // nenhum filho ou um filho - troca pela z pelo filho de z (se não tiver nenhum filho, o filho é nullptr)
        if (todie->left == nullptr) {
            transplante(todie, todie->right);
        } else if (todie->right == nullptr) {
            transplante(todie, todie->left);
        } else {
            Node* y = min(todie->right);
            
            todie->data = y->data; 

            Node* pai_y = y->parent;
            
            if (y->parent->left == y) {
                y->parent->left = y->right;
            } else {
                y->parent->right = y->right;
            }
            
            if (y->right != nullptr) {
                y->right->parent = y->parent;
            }

            Node* pai = pai_y;
            while (pai != nullptr) {
                atualizar_altura(pai);
                balance(pai);
                pai = pai->parent;
            }

            delete y;
            return;
        }
    }

    void inorder(int k) {
        bool achou = false;
        iorec(root, k, achou);
        if (!achou) {
            cout << "NENHUM" << endl;
        }
    }
};

class HashTable {
private:
    struct HashNode {
        InfoReagente data;
        bool ocupado;
        bool removido;

        HashNode() : ocupado(false), removido(false) {}
        HashNode(InfoReagente d) : data(d), ocupado(false), removido(false) {}
    };

    HashNode tabela[ht_size];

    // polynomial rolling hash function é eficiente porque dispersa bem
    int hash_function(string s) {
        ll index = 0;
        int base = 7;
        ll pow = 1;

        for (char c : s) {
            index = (index + c * pow) % ht_size;
            pow = (pow * base) % ht_size;
        }

        return index;
    }

    int search_index(string nome) {
        int idx = hash_function(nome);

        while (tabela[idx].ocupado == true || tabela[idx].removido == true) {
            if (tabela[idx].ocupado == true && tabela[idx].data.nome == nome) {
                return idx;
            }

            idx = (idx + 1) % ht_size;
        }

        return -1;
    }

public:
    int search(string nome) {
        int idx = search_index(nome);

        if (idx != -1) {
            return tabela[idx].data.quantidade;
        }

        return -1;
    }

    void insert_update(InfoReagente data) {
        int idx = hash_function(data.nome);
        int primeiro_removido = -1;

        while (tabela[idx].ocupado == true || tabela[idx].removido == true) {
            // atualização do valor
            if (tabela[idx].ocupado == true && tabela[idx].data.nome == data.nome) {
                tabela[idx].data.quantidade = data.quantidade;
                return;
            }

            // guarda espaço encontrado no caminho -> reciclagem do espaço novo a partir do primeiro elemento removido encontrado
            if (tabela[idx].ocupado == false && tabela[idx].removido == true && primeiro_removido == -1) {
                primeiro_removido = idx;
            }

            idx = (idx + 1) % ht_size;
        }

        // reagente novo
        int alvo = (primeiro_removido != -1) ? primeiro_removido : idx;

        tabela[alvo].data = data;
        tabela[alvo].ocupado = true;
        tabela[alvo].removido = false;
    }

    void remove(string nome) {
        int idx = search_index(nome);

        if (idx != -1) {
            tabela[idx].ocupado = false;
            tabela[idx].removido = true;
        }
    }
};

AVL tree;
HashTable ht;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int op; cin >> op;
    string operacao, nome;
    int qtd, k, consumo;

    while (op--) {
        cin >> operacao;

        if (operacao == "ENTRADA") {
            cin >> nome >> qtd;

            int qtd_antiga = ht.search(nome);
            
            if (qtd_antiga != -1) {
                tree.delete_node({qtd_antiga, nome});
            }

            int qtd_nova = (qtd_antiga != -1) ? qtd_antiga + qtd : qtd;

            InfoReagente toadd = InfoReagente(qtd_nova, nome);
            tree.insert(toadd);
            ht.insert_update(toadd);

        } else if (operacao == "CONSUMO") {
            cin >> nome >> consumo;

            int qtd_antiga = ht.search(nome);

            if (qtd_antiga != -1) {
                tree.delete_node({qtd_antiga, nome});

                int qtd_nova = qtd_antiga - consumo;

                if (qtd_nova > 0) {
                    InfoReagente toadd = InfoReagente(qtd_nova, nome);

                    ht.insert_update(toadd);
                    tree.insert(toadd);
                } else {
                    ht.remove(nome);
                }
            }

        } else if (operacao == "CONSULTA") {
            cin >> nome;
            
            int qtd = ht.search(nome);

            if (qtd > 0) cout << qtd << endl;
            else cout << "AUSENTE" << endl;


        } else if (operacao == "CRITICOS") {
            cin >> k;
            tree.inorder(k);
        }
    }

    return 0;
}
