#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

class BST {
private:
    struct Node {
        int value;
        Node* left = nullptr;
        Node* right = nullptr;
    };

public:
    Node* root = nullptr;

    void insert(int value);
    void post_order(Node* cur);
};


void BST::insert(int value) {
    Node* cur = root;
    Node* parent = nullptr;

    Node* toAdd = new Node;
    toAdd->value = value;

    while (cur != nullptr) {
        parent = cur;

        cur = toAdd->value < cur->value ? cur->left : cur->right;
    }

    if (parent == nullptr) {
        root = toAdd;
    } else if (toAdd->value < parent->value) {
        parent->left = toAdd;
    } else {
        parent->right = toAdd;
    }
}

void BST::post_order(Node* cur) {
    if (cur == nullptr) return;

    post_order(cur->left);
    post_order(cur->right);
    cout << cur->value << endl;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    BST tree;

    while (cin >> x) {
        tree.insert(x);
    }

    tree.post_order(tree.root);

    return 0;
}