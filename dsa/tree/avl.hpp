#include <iostream>

using namespace std;

class AVL {
private:
    struct Node {
        int value;
        int height; // altura máxima do meu nó até uma folha
        Node* left;
        Node* right;
        Node* parent;

        Node(int k) : value(k), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

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

public:
    AVL() {
        root = nullptr;
    }

    void insert(int x) {
        Node* cur = root;
        Node* y = nullptr;

        while (cur != nullptr) {
            y = cur;

            if (cur->value > x) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }

        Node* newnode = new Node(x);
        newnode->parent = y;

        if (y == nullptr) {
            root = newnode;
        } else if (newnode->value > y->value) {
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
};