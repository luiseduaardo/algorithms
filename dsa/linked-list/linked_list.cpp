#include <bits/stdc++.h>
#include "linked_list.hpp"
#define spc " "
#define endl "\n"

using namespace std;

int main() {
    DoublyLinkedList<int> DLL;

    DLL.insert(2);
    DLL.insert(4);
    DLL.insert(5);
    DLL.insert(10);
    DLL.insert(9);

    DLL.remove(10);
    DLL.remove(5);
    DLL.remove(10);

    DLL.search(2);

    return 0;
}