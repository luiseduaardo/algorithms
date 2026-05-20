#include <iostream>
#define spc " "
#define endl "\n"

using namespace std;

class BST {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void iorec(Node* root) {
        if (root == nullptr) return;

        iorec(root->left);
        cout << root->value << spc;
        iorec(root->right);
    }

    void prerec(Node* root) {
        if (root == nullptr) return;

        cout << root->value << spc;
        prerec(root->left);
        prerec(root->right);
    }

    void postrec(Node* root) {
        if (root == nullptr) return;

        postrec(root->left);
        postrec(root->right);
        cout << root->value << spc;
    }

    Node* searchrec(Node* root, int k) {
        if (root == nullptr || root->value == k) {
            return root;
        }

        if (k > root->value) {
            return searchrec(root->right, k);
        } else {
            return searchrec(root->left, k);
        }

    }

    Node* insertrec(Node* root, int k) {
        Node* newnode;

        if (root == nullptr) {
            newnode = new Node(k);
            return newnode;
        }

        if (k > root->value) {
            root->right = insertrec(root->right, k);
            root->right->parent = root;
        } else if (k < root->value) {
            root->left = insertrec(root->left, k);
            root->left->parent = root;
        }

        return root;
    }

    // substitui a subárvore com raiz em u pela subávore com raiz em v
    // fazemos transplante controlado na operação de remoção
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

    int hrec(Node* root) {
        if (root == nullptr) return 0;

        int left_height = hrec(root->left);
        int right_height = hrec(root->right);

        int max = (left_height > right_height) ? left_height : right_height;

        return 1 + max;
    }

public:
    BST() { root = nullptr; }

    void inorder() {
        iorec(root);
    }

    void preorder() {
        prerec(root);
    }

    void postorder() {
        postrec(root);
    }

    Node* search_recursive(int k) {
        return searchrec(root, k);
    }

    Node* search_iterative(int k) {
        Node* cur = root;

        while (cur != nullptr) {
            if (k > cur->value) {
                cur = cur->right;
            } else if (k < cur->value) {
                cur = cur->left;
            } else {
                return cur;
            }
        }

        return nullptr;
    }

    Node* min(Node* no) {
        Node* cur = no;

        while (cur->left != nullptr) {
            cur = cur->left;
        }

        return cur;
    }

    Node* max(Node* no) {
        Node* cur = no;

        while (cur->right != nullptr) {
            cur = cur->right;
        }

        return cur;
    }

    Node* sucessor(int k) {
        Node* no = search_iterative(k);

        // caso 1: se eu tenho um nó a direita, vai ser o menor valor dessa subárvore
        if (no->right) {
            return min(no->right);
        }

        // caso 2: se eu não tenho um nó a direita, subimos na árvore até encontrar o primeiro deslocamento a esquerda que aconteceu
        Node* y = no->parent;
        while (y && no == y->right) {
            no = y;
            y = y->parent;
        }

        return y;
    }

    Node* predecessor(int k) {
        Node* no = search_iterative(k);

        // caso 1: se eu tenho um nó a esquerda, vai ser o maior valor dessa subárvore
        if (no->left) {
            return max(no->left);
        }

        // caso 2: se eu não tenho um nó a esquerda, subimos na árvore até encontrar o primeiro deslocamento a direita que aconteceu
        Node* y = no->parent;
        while (y && no == y->left) {
            no = y;
            y = y->parent;
        }

        return y;
    }

    int height() {
        return hrec(root);
    }

    void insert_iterative(int k) {
        Node* newnode = new Node(k);
        Node* parent = nullptr;
        Node* cur = root;

        while (cur != nullptr) {
            parent = cur;

            if (cur->value == k) {
                return; // valor já está na árvore (não pode ser inserido)
            } else if (cur->value > k) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }

        newnode->parent = parent;

        if (parent == nullptr) {
            root = newnode;
        } else if (newnode->value > parent->value) {
            parent->right = newnode;
        } else {
            parent->left = newnode;
        }
    }

    Node* insert_recursive(int k) {
        return insertrec(root, k);
    }

    void delete_node(int k) {
        Node* todie = search_iterative(k);

        // nenhum filho ou um filho - troca pela z pelo filho de z (se não tiver nenhum filho, o filho é nullptr)
        if (todie->left == nullptr) {
            transplante(todie, todie->right);
        } else if (todie->right == nullptr) {
            transplante(todie, todie->left);
        } else {
            // caso em que o nó a ser deletado tem dois filhos

            // encontra o sucessor imediato do nó a ser deletado
            Node* y = min(todie->right); // também poderia usar a função de sucessor
            // Node* y = sucessor(todie->value);

            // se o sucessor não for filho do nó a ser removido
            if (y->parent != todie) {
                transplante(y, y->right);
                y->right = todie->right;
                y->right->parent = y;
            }

            transplante(todie, y);
            y->left = todie->left;
            todie->left->parent = y;
        }
    }
};