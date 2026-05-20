#include <bits/stdc++.h>
#define endl '\n'
#define spc ' '

using namespace std;

class BST {
private:
    struct Node {
        string name;
        int time;
        Node* left;
        Node* right;

        Node(string n, int t) : name(n), time(t), left(nullptr), right(nullptr) {}
    };

    void io_rec(Node* n) {
        if (n == nullptr) return;

        io_rec(n->left);
        cout << n->name << spc << n->time << endl;
        io_rec(n->right);
    }
    Node* root;

public:
    BST() {
        root = nullptr;
    }

    void insert(string n, int t) {
        Node* to_add = new Node(n, t);

        Node* y = nullptr;
        Node* cur = root;

        while (cur != nullptr) {
            y = cur;

            if (cur->time < t || (cur->time == t && cur->name < n)) {
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }

        if (y == nullptr) {
            root = to_add;
        } else if (t > y->time || (t == y->time && n > y->name)) {
            y->right = to_add;
        } else {
            y->left = to_add;
        }
    }

    void inorder() {
        io_rec(this->root);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int participantes; cin >> participantes;

    BST tree;
    string nome;
    int tempo;

    while (participantes--) {
        cin >> nome >> tempo;
        tree.insert(nome, tempo);
    }

    tree.inorder();

    return 0;
}
