#include <bits/stdc++.h>
#include "bst.hpp"
#define endl "\n"
#define spc " "

using namespace std;

int main() {
    BST tree;

    tree.insert_iterative(30);
    tree.insert_iterative(5);
    tree.insert_iterative(15);
    tree.insert_iterative(3);
    tree.insert_iterative(60);
    tree.insert_iterative(45);
    tree.insert_iterative(6);
    tree.insert_iterative(2);

    tree.delete_node(5);
    tree.delete_node(60);
    tree.delete_node(15);

    tree.insert_iterative(10);
    tree.insert_iterative(7);
    tree.insert_iterative(1);

    tree.delete_node(2);

    tree.inorder();

    return 0;
}